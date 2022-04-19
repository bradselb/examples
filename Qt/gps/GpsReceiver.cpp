#include "GpsReceiver.h"

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QString>


#include <QDebug>

// ---------------------------------------------------------------------------
int verify_checksum(QByteArray);



// ---------------------------------------------------------------------------
GpsReceiver::GpsReceiver(QIODevice* iodevice, QObject* parent) : QObject(parent), m_iodevice(iodevice)
{
    bool isSuccess = m_iodevice->open(QIODevice::ReadOnly);
    if (!isSuccess) {
        qDebug() << "iodevice open() error code: " << m_iodevice->errorString();
    }

    connect(m_iodevice, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}


// ---------------------------------------------------------------------------
GpsReceiver::~GpsReceiver()
{
    if (m_iodevice) {
        m_iodevice->close();
    }
}


// ---------------------------------------------------------------------------
void GpsReceiver::onReadyRead()
{
    char buf[128];
    int length;

    if (m_iodevice->canReadLine()) {
        length = m_iodevice->readLine(buf, sizeof buf);
        if (length<0) {
            qDebug() << "iodevice read() failed. ";
        } else {
            QByteArray receivedLine(QByteArray(buf).trimmed());

            if (receivedLine[0] != '$' || !receivedLine.contains('*')) {
                qDebug() << "recieved an incomplete line.";
            } else if (!verify_checksum(receivedLine)) {
                qDebug() << "recieved a line of garbage.";
            } else {

                emit nmeaSentence(QString(buf));
            }
        }
    }
}


// ---------------------------------------------------------------------------
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

