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
                    hours = tokens[1].mid(0,2).toInt();
                    minutes =  tokens[1].mid(2,2).toInt();
                    seconds = tokens[1].mid(4,2).toInt();
                    QTime time(hours, minutes, seconds, 0);
                    //emit updateTime(time);

                    // second token is latitude. ddmm.mmmm
                    // third token is 'N' or 'S'
                    double degrees = tokens[2].mid(0,2).toInt();
                    degrees += (tokens[2].mid(2,7).toDouble()) / 60.0;
                    double latitude = (tokens[3]=="S" ? -1.0 : 1.0) * degrees;
                    emit updateLatitude(latitude);

                    // fourth token is longitude. dddmm.mmmm
                    // fifth token is 'E' or 'W'
                    degrees = tokens[4].mid(0,3).toInt();
                    degrees += (tokens[4].mid(3,7).toDouble()) / 60.0;
                    double longitude = (tokens[5]=="W" ? -1.0 : 1.0) * degrees;
                    emit updateLongitude(longitude);

                    // sixth token indicates type of fix 0:fix not valid, 1:GPS fix, 2:DGPS fix
                    int fix = tokens[6].toInt();
                    emit updateFixQuality(fix);

                    // seventh token is, number of satelites used to calculate the fix
                    int satsUsed = tokens[7].toInt();
                    emit updateSatellitesUsed(satsUsed);

                    // eighth token is horizontal dilution of precision, hdop
                    double hdop = tokens[8].toDouble();
                    emit updateHDOP(hdop);

                    // nineth token is antenna height above mean sea level in meters.
                    // and the eleventh token is the geoidal separation in meters. 
                    //double antennaHeight = tokens[9].toDouble();
                    //double geoidalSeparation = tokens[11].toDouble();
                    //double altitude = antennaHeight + geoidalSeparation;
                    emit updateAltitude(tokens[9].toDouble()); // above mean sea level in meters

                    //qDebug() << time.toString() 
                    //         << QString("lat, lon: %1, %2").arg(latitude, 0, 'f', -1).arg(longitude, 0, 'f', -1)
                    //         << QString("altitude: %1 meters").arg(altitude, 0, 'f', -1) 
                    //         << QString("Satellites used: %1").arg(satsUsed) << QString("dop: %1").arg(dop,0,'f', -1);

                } else if (tokens[0].mid(2,3) == QString("RMC")) {
                    // first token is UTC hhmmss.sss
                    int hours, minutes, seconds;
                    hours = tokens[1].mid(0,2).toInt();
                    minutes =  tokens[1].mid(2,2).toInt();
                    seconds = tokens[1].mid(4,2).toInt();
                    QTime time(hours, minutes, seconds, 0);
                    emit updateTime(time);

                    // second token is a single letter. A-->valid fix, V-->not valid fix
                    emit updateFixValid(tokens[2]);

                    // third token is latitude. ddmm.mmmm
                    // fourth token is 'N' or 'S'
                    double degrees = tokens[3].mid(0,2).toInt();
                    degrees += (tokens[3].mid(2,7).toDouble()) / 60.0;
                    double latitude = (tokens[4]=="S" ? -1.0 : 1.0) * degrees;
                    emit updateLatitude(latitude);

                    // fifth token is longitude. dddmm.mmmm
                    // sixth token is 'E' or 'W'
                    degrees = tokens[5].mid(0,3).toInt();
                    degrees += (tokens[5].mid(3,7).toDouble()) / 60.0;
                    double longitude = (tokens[6]=="W" ? -1.0 : 1.0) * degrees;
                    emit updateLongitude(longitude);

                    // seventh and eighth are two floating point numbers...
                    // speed in knots and heading
                    //double speed = tokens[7].toDouble();
                    double heading = tokens[8].toDouble();
                    emit updateHeading(heading);

                    // ninth token is the date, ddmmyy
                    int day, month, year;
                    day = tokens[9].mid(0,2).toInt();
                    month = tokens[9].mid(2,2).toInt();
                    year =  tokens[9].mid(4,2).toInt() + 2000;
                    QDate date(year, month, day);
                    emit updateDate(date);

                    // twelfth token is a single letter indicating mode {N,A,D}
                    emit updateFixMode(tokens[12]);

                    //QDateTime datetime(date, time, QTimeZone(0)); // this is key to getting the correct time zone
                    //qDebug() << datetime.toString(Qt::ISODate) << QString("lat, lon: %1, %2").arg(latitude, 0, 'f', 6).arg(longitude, 0, 'f', 6) << datetime.toLocalTime().toString("ddd, dd MMM yyyy hh:mm:ss a");
                } else if (tokens[0] == QString("GPGSV")) {
                    emit updateGpsSatInView(tokens[3].toInt());
                } else if (tokens[0] == QString("GLGSV")) {
                    emit updateGlonasInView(tokens[3].toInt());
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


