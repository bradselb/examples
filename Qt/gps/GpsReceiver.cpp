#include "GpsReceiver.h"

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QString>

#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QTimeZone>

#include <QDebug>

int verify_checksum(QByteArray);
int decodeUTC(QString const& token, int* hours, int* minutes, int* seconds);
int decodeLatLon(QString const& magnitude, QString const& direction, double* degrees);



GpsReceiver::GpsReceiver(QObject* parent, QIODevice* port) : QObject(parent),m_port(port)
{
    bool isSuccess = m_port->open(QIODevice::ReadOnly);
    if (!isSuccess) {
        qDebug() << "port open() error code: " << m_port->errorString();
    }

    connect(m_port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}


GpsReceiver::~GpsReceiver()
{
    if (m_port) {
        m_port->close();
    }
}


void GpsReceiver::onReadyRead()
{
    char buf[128];
    int length;

    if (m_port->canReadLine()) {
        length = m_port->read(buf, -1 + sizeof buf);
        if (length<=0) {
            qDebug() << "port read() failed. ";
        } else {
            buf[length] = 0;
            int i = length - 1;
            while (buf[i] == '\r' || buf[i] == '\n') {
                buf[i--] = 0;
            }

            QByteArray receivedLine(buf);
            if (receivedLine[0] != '$' || !receivedLine.contains('*')) {
                qDebug() << "recieved an incomplete line.";
            } else if (!verify_checksum(receivedLine)) {
                qDebug() << "recieved a line of garbage.";
            } else {

                QString s(buf);
                QStringList parts = s.split('*');
                QString message = parts[0].remove('$');
                //qDebug() << message;

                emit messageReceived(message); // let others know.


                // factor this out.
                QStringList tokens = message.split(','); //keep the empty fields
                if (tokens[0].mid(2,3) == QString("GGA")) {
                    // first token is UTC hhmmss.sss
                    int hours, minutes, seconds;
                    decodeUTC(tokens[1], &hours, &minutes, &seconds);
                    QTime time(hours, minutes, seconds, 0);
                    //emit updateTime(time);

                    // second token is latitude. ddmm.mmmm
                    // third token is 'N' or 'S'
                    double degrees;
                    int ec = decodeLatLon(tokens[2], tokens[3], &degrees);
                    if (!ec) emit updateLatitude(degrees);

                    // fourth token is longitude. dddmm.mmmm
                    // fifth token is 'E' or 'W'
                    ec = decodeLatLon(tokens[4], tokens[5], &degrees);
                    if (!ec) emit updateLongitude(degrees);

                    // sixth token indicates type of fix 0:fix not valid, 1:GPS fix, 2:DGPS fix
                    emit updateFixQuality(tokens[6].toInt());

                    // seventh token is, number of satelites used to calculate the fix
                    emit updateSatellitesUsed(tokens[7].toInt());

                    // eighth token is horizontal dilution of precision, hdop
                    emit updateHDOP(tokens[8].toDouble());

                    // nineth token is antenna height above mean sea level, in meters.
                    //double antennaHeight = tokens[9].toDouble();
                    // and the eleventh token is the geoidal separation in meters. 
                    //double geoidalSeparation = tokens[11].toDouble();
                    //double height = antennaHeight + geoidalSeparation;
                    // the above is the height, in meters, above the elipsoid surface?

                    emit updateAltitude(tokens[9].toDouble()); // above mean sea level in meters

                    //qDebug() << time.toString() 
                    //         << QString("lat, lon: %1, %2").arg(latitude, 0, 'f', -1).arg(longitude, 0, 'f', -1)
                    //         << QString("altitude: %1 meters").arg(altitude, 0, 'f', -1) 
                    //         << QString("Satellites used: %1").arg(satsUsed) << QString("dop: %1").arg(dop,0,'f', -1);

                } else if (tokens[0].mid(2,3) == QString("RMC")) {
                    // first token is UTC hhmmss.sss
                    int hours, minutes, seconds;
                    decodeUTC(tokens[1], &hours, &minutes, &seconds);
                    QTime time(hours, minutes, seconds, 0);
                    emit updateTime(time);

                    // second token is a single letter indicating fix status, A-->valid fix, V-->not valid fix
                    emit updateFixStatus(tokens[2]);

                    // third token is latitude. ddmm.mmmm
                    // fourth token is 'N' or 'S'
                    double degrees;
                    int ec = decodeLatLon(tokens[3], tokens[4], &degrees);
                    if (!ec) emit updateLatitude(degrees);

                    // fifth token is longitude. dddmm.mmmm
                    // sixth token is 'E' or 'W'
                    ec = decodeLatLon(tokens[5], tokens[6], &degrees);
                    if (!ec) emit updateLongitude(degrees);

                    // I'm not sure these are reliable.
                    //double speed = tokens[7].toDouble(); // knots?
                    //double heading = tokens[8].toDouble();
                    //emit updateHeading(tokens[8].toDouble());

                    // ninth token is the UTC date, ddmmyy
                    int day, month, year;
                    day = tokens[9].mid(0,2).toInt();
                    month = tokens[9].mid(2,2).toInt();
                    year =  tokens[9].mid(4,2).toInt() + 2000;
                    QDate date(year, month, day);
                    emit updateDate(date);

                    // twelfth token is a single letter indicating mode {N,A,D}
                    emit updateFixMode(tokens[12]);

                } else if (tokens[0].mid(2,3) == QString("VTG")) {
                } else if (tokens[0] == QString("GPGSV")) {
                    emit updateGpsSatsInView(tokens[3].toInt());
                } else if (tokens[0] == QString("GLGSV")) {
                    emit updateGloSatsInView(tokens[3].toInt());
                }
            }
        }
    }
}



int verify_checksum(QByteArray receivedSentence)
{
    int isGood;
    unsigned int sum; // sum of the data bytes in the message
    unsigned int checksum; // the actual checksum from the end of the sentence
    bool isSuccess;


    // separate the message part from the checksum part at the end.
    QList<QByteArray> parts = receivedSentence.split('*');

    QByteArray message(parts[0]); // just convenient notation.

    // iterate over the bytes of the message part and sum up the bytes.
    QByteArray::const_iterator iter = message.begin();
    ++iter; // skip the '$' at the beginning.
    sum = 0;
    while (iter != message.end()) {
        sum ^= *iter++;
    }

    // get the received checksum value from the end of the sentence
    checksum = parts[1].toUInt(&isSuccess, 16);

    isGood = isSuccess && (sum == checksum);

    return isGood;
}

int decodeUTC(QString const& token, int* hours, int* minutes, int* seconds)
{
    int rc = 0;

    if (0 != hours) *hours = token.mid(0,2).toInt();
    if (0 != minutes) *minutes =  token.mid(2,2).toInt();
    if (0 != seconds) *seconds = token.mid(4,2).toInt();

    return rc;
}

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
