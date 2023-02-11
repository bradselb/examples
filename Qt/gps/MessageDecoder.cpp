#include "MessageDecoder.h"

#include <QObject>
#include <QString>
#include <QTime>
#include <QDate>

#include <QDebug>

// ---------------------------------------------------------------------------
// local functions
static int decodeUTC(QString const& token, int* hours, int* minutes, int* seconds);
static int decodeDate(QString const& token, int* day, int* month, int* year);
static int decodeLatLon(QString const& magnitude, QString const& direction, double* degrees);




// ---------------------------------------------------------------------------
MessageDecoder::MessageDecoder(QObject* parent) : QObject(parent)
{
}


// ---------------------------------------------------------------------------
MessageDecoder::~MessageDecoder()
{
}


// ---------------------------------------------------------------------------
void MessageDecoder::decodeNmeaSentence(QString const& sentence)
{
    // throw away the checksum and the '$' and '*',
    // keep only the message part
    QStringList parts = sentence.split('*');
    QString message = parts[0].remove('$');

    // split the message into a list of tokens. Keep the empty fields
    QStringList tokens = message.split(',');

    if (tokens[0].contains("GGA")) {
        decodeGGA(tokens);

    } else if (tokens[0].contains("GSA")) {
        decodeGSA(tokens);

    } else if (tokens[0].contains("RMC")) {
        decodeRMC(tokens);

    } else if (tokens[0].contains("VTG")) {
        decodeVTG(tokens);

    } else if (tokens[0].contains("GSV")) {
        decodeGSV(tokens);

    } else if (tokens[0].contains("PMTK")) {
        // a proprietary MTK sentence.
        emit proprietaryMessageReceived(message);
    }
}


// ---------------------------------------------------------------------------
int MessageDecoder::decodeGGA(QStringList const& tokens)
{
    // first token is UTC, format is, hhmmss.sss
    int hours, minutes, seconds;
    decodeUTC(tokens[1], &hours, &minutes, &seconds);
    emit time(QTime(hours, minutes, seconds, 0));

    // second token is latitude. format is, ddmm.mmmm
    // third token is 'N' or 'S'
    double lat;
    int ec = decodeLatLon(tokens[2], tokens[3], &lat);
    //if (!ec) emit latitude(degrees);

    // fourth token is longitude. dddmm.mmmm
    // fifth token is 'E' or 'W'
    double lon;
    ec |= decodeLatLon(tokens[4], tokens[5], &lon);
    //if (!ec) emit longitude(degrees);

    // 0:no fix, 1:GPS fix, 2:DGPS fix
    int fixquality = tokens[6].toInt();
    emit fixQuality(fixquality);

    // seventh token is the number of satellites used in the fix.
    int sats = tokens[7].toInt();
    emit satsInUse(sats);

    // eighth token is horizontal dilution of precision, hdop
    double hdop = tokens[8].toDouble();
    //emit hdop(hdop); // redundant hdop in GSA

    double antennaHeight = tokens[9].toDouble(); //above mean sea level, in meters.
    emit altitude(antennaHeight);

    double geoidalSeparation = tokens[11].toDouble();
    //double heightAboveElipsoid = antennaHeight + geoidalSeparation;

    if (!ec) {
        emit GGA(hours, minutes, seconds, lat, lon, fixquality, sats, hdop, antennaHeight, geoidalSeparation);
    }

    return 0;
}


// ---------------------------------------------------------------------------
int MessageDecoder::decodeGSA(QStringList const& tokens)
{
    int active_sat_count = 0;
    for (int i=0; i<12; ++i) {
        int prn; // satellite vehicle (ID) number?
        bool ok;

        prn = tokens[i+3].toInt(&ok);
        if (ok) {
            emit activeSatPRN(prn);
            ++active_sat_count;
        }
    }
    emit activeSatCount(active_sat_count);

    emit fixType(tokens[2].toInt()); // 1--> no fix, 2--> 2d fix, 3-->3d fix
    emit pdop(tokens[15].toDouble());
    emit hdop(tokens[16].toDouble());
    emit vdop(tokens[17].toDouble());
    return 0;
}


// ---------------------------------------------------------------------------
int MessageDecoder::decodeGSV(QStringList const& tokens)
{
    int val;
    bool ok;

    // first token is message count - how many GSV messages in this group?
    //val = tokens[1].toInt(&ok);
    //int msg_count = (ok ? val : 1);

    // second token is message number - which message in this group of GSV messages
    val = tokens[2].toInt(&ok);
    int msg_nr = (ok ? val : 1);

    // third token is the total number of satellites in view - even if not active in fix
    val = tokens[3].toInt(&ok);
    int sats_in_view = (ok ? val : 0);

    if (tokens[0].contains("GP")) {
        emit gpsSatsInView(sats_in_view);
    } else if (tokens[0].contains("GL")) {
        emit gloSatsInView(sats_in_view);
    }

    // each GSV message contains info on up to four satellites. In fact, it appears that
    // each GSV message has 4*4 satellite info fields even if they are blank.
    // this next bit is trying to figure out how many non-empty sets of satellite info
    // are contained in this GSV message. It is a number between 1 and 4 inclusive.
    int msg_idx = msg_nr - 1;
    int sats_this_msg = 0;
    if (msg_idx < sats_in_view/4) {
        sats_this_msg = 4;
    } else
    if (msg_idx == sats_in_view/4) {
        sats_this_msg = sats_in_view % 4;
    }

    for (int i=0; i<sats_this_msg; ++i) {
        int prn;
        int elev;
        int azim;
        int snr;

        val = tokens[4 + 4*i].toInt(&ok);
        prn = (ok ? val : -1);

        val = tokens[5 + 4*i].toInt(&ok);
        elev = (ok ? val : -1);

        val = tokens[6+ 4*i].toInt(&ok);
        azim = (ok ? val : -1);

        val = tokens[7+ 4*i].toInt(&ok);
        snr = (ok ? val : -1);

        emit satInView(prn, azim, elev, snr);
    }

    return 0;
}

// ---------------------------------------------------------------------------
int MessageDecoder::decodeRMC(QStringList const& tokens)
{
    // first token is UTC hhmmss.sss
    int hours, minutes, seconds;
    decodeUTC(tokens[1], &hours, &minutes, &seconds);
    emit time(QTime(hours, minutes, seconds, 0));

    // second token is a single letter indicating fix status, A-->valid fix, V-->not valid fix
    emit fixStatus(tokens[2].at(0));
    int fixstatus = tokens[2].at(0).cell();

    // third token is latitude, ddmm.mmmm and the fourth token is 'N' or 'S'
    double lat=0.0;
    int ec = decodeLatLon(tokens[3], tokens[4], &lat);
    if (!ec) emit latitude(lat);

    // fifth token is longitude, dddmm.mmmm and the sixth token is 'E' or 'W'
    double lon=0.0;
    ec = decodeLatLon(tokens[5], tokens[6], &lon);
    if (!ec) emit longitude(lon);

    // ninth token is the UTC date, ddmmyy
    int day, month, year;
    decodeDate(tokens[9], &day, &month, &year);
    emit date(QDate(year, month, day));

    // twelfth token is a single letter indicating mode {N,A,D}
    emit fixMode(tokens[12].at(0));
    int fixmode = tokens[12].at(0).cell();

    emit RMC(hours, minutes, seconds, fixstatus, lat, lon, day, month, year, fixmode);

    return 0;
}


// ---------------------------------------------------------------------------
int MessageDecoder::decodeVTG(QStringList const& tokens)
{
    emit directionOfTravel(tokens[1].toDouble());
    emit speedOfTravelKmPerHr(tokens[7].toDouble());
    return 0;
}



// ---------------------------------------------------------------------------
int decodeDate(QString const& token, int* day, int* month, int* year)
{
    int rc = 0;
    if (0 != day) *day = token.mid(0,2).toInt();
    if (0 != month) *month = token.mid(2,2).toInt();
    if (0 != year) *year =  token.mid(4,2).toInt() + 2000;

    return rc;
}

// ---------------------------------------------------------------------------
int decodeUTC(QString const& token, int* hours, int* minutes, int* seconds)
{
    int rc = 0;

    if (0 != hours) *hours = token.mid(0,2).toInt();
    if (0 != minutes) *minutes =  token.mid(2,2).toInt();
    if (0 != seconds) *seconds = token.mid(4,2).toInt();

    return rc;
}

// ---------------------------------------------------------------------------
// decode either latitude or longitude.
// latitide  is encoded, ddmm.mmmm
// longitude is encoded, dddmm.mmmm
// strategy will be look for the decimal point and back up two characters.
int decodeLatLon(QString const& magnitude, QString const& direction, double* degrees)
{
    int rc;
    int idx;
    double d;

    // find the decimal point, expect it to be either 4 or 5
    idx = magnitude.indexOf(QChar('.'));
    if (idx == 4 || idx == 5) {
        idx = idx - 2; // now the index of the start of 'mm.mmmm'
        d = magnitude.left(idx).toDouble();
        d += magnitude.mid(idx, 7).toDouble() / 60.0;
        if (direction == "W" || direction == "S") {d = -1.0 * d;}
        if (degrees) *degrees = d;
        rc = 0;
    } else {
        rc = -1;
    }

    return rc;
}

