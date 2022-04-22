#include "MessageDecoder.h"

#include <QObject>
#include <QString>
#include <QTime>
#include <QDate>


// ---------------------------------------------------------------------------
// local functions
static int decodeUTC(QString const& token, int* hours, int* minutes, int* seconds);
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

    if (tokens[0].mid(2,3) == QString("GGA")) {
        decodeGGA(tokens);

    } else if (tokens[0].mid(2,3) == QString("GSA")) {
        emit updatePdop(tokens[15].toDouble());
        emit updateHdop(tokens[16].toDouble());
        emit updateVdop(tokens[17].toDouble());

    } else if (tokens[0].mid(2,3) == QString("RMC")) {
        decodeRMC(tokens);

    } else if (tokens[0].mid(2,3) == QString("VTG")) {
        emit updateDirectionOfTravel(tokens[1].toDouble());
        emit updateSpeedOfTravelKmPerHr(tokens[7].toDouble());

    } else if (tokens[0] == QString("GPGSV")) {
        emit updateGpsSatsInView(tokens[3].toInt());

    } else if (tokens[0] == QString("GLGSV")) {
        emit updateGloSatsInView(tokens[3].toInt());
    }
}


// ---------------------------------------------------------------------------
int MessageDecoder::decodeGGA(QStringList const& tokens)
{ 
    // first token is UTC, format is, hhmmss.sss
    //int hours, minutes, seconds;
    //decodeUTC(tokens[1], &hours, &minutes, &seconds);
    //QTime time(hours, minutes, seconds, 0);
    //emit updateTime(time);

    // second token is latitude. format is, ddmm.mmmm
    // third token is 'N' or 'S'
    //double degrees;
    //int ec = decodeLatLon(tokens[2], tokens[3], &degrees);
    //if (!ec) emit updateLatitude(degrees);

    // fourth token is longitude. dddmm.mmmm
    // fifth token is 'E' or 'W'
    //ec = decodeLatLon(tokens[4], tokens[5], &degrees);
    //if (!ec) emit updateLongitude(degrees);

    // sixth token indicates type of fix 0:fix not valid, 1:GPS fix, 2:DGPS fix
    emit updateFixQuality(tokens[6].toInt());

    // seventh token is, number of satellites used to calculate the fix
    emit updateSatsInUse(tokens[7].toInt());

    // eighth token is horizontal dilution of precision, hdop
    //emit updateHDOP(tokens[8].toDouble());

    // ninth token is antenna height above mean sea level, in meters.
    //double antennaHeight = tokens[9].toDouble();
    // eleventh token is the geoidal separation in meters.
    //double geoidalSeparation = tokens[11].toDouble();
    //double height = antennaHeight + geoidalSeparation;
    // the above is the height, in meters, above the surface of the ellipsoid?

    emit updateAltitude(tokens[9].toDouble()); // above mean sea level in meters

    return 0;
}

// ---------------------------------------------------------------------------
int MessageDecoder::decodeRMC(QStringList const& tokens)
{ 
    // first token is UTC hhmmss.sss
    int hours, minutes, seconds;
    decodeUTC(tokens[1], &hours, &minutes, &seconds);
    QTime time(hours, minutes, seconds, 0);
    if (time.isValid() && !time.isNull()) emit updateTime(time);

    // second token is a single letter indicating fix status, A-->valid fix, V-->not valid fix
    emit updateFixStatus(tokens[2].at(0));

    // third token is latitude, ddmm.mmmm and the fourth token is 'N' or 'S'
    double degrees;
    int ec = decodeLatLon(tokens[3], tokens[4], &degrees);
    if (!ec) emit updateLatitude(degrees);

    // fifth token is longitude, dddmm.mmmm and the sixth token is 'E' or 'W'
    ec = decodeLatLon(tokens[5], tokens[6], &degrees);
    if (!ec) emit updateLongitude(degrees);

    // ninth token is the UTC date, ddmmyy
    int day, month, year;
    day = tokens[9].mid(0,2).toInt();
    month = tokens[9].mid(2,2).toInt();
    year =  tokens[9].mid(4,2).toInt() + 2000;
    QDate date(year, month, day);
    if (date.isValid() && !date.isNull()) emit updateDate(date);

    // twelfth token is a single letter indicating mode {N,A,D}
    emit updateFixMode(tokens[12].at(0));

    return 0;
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

