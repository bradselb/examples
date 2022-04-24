#include "GpsReceiver.h"

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QString>

#include <stdlib.h> // memset()
#include <stdio.h> // sprintf()

//#include <QDebug>

// ---------------------------------------------------------------------------
static unsigned int calculateChecksum(QByteArray const& message);
static int verifyChecksum(QByteArray);



// ---------------------------------------------------------------------------
GpsReceiver::GpsReceiver(QIODevice* iodevice, QObject* parent) : QObject(parent), m_iodevice(iodevice)
{
    bool isSuccess = m_iodevice->open(QIODevice::ReadWrite);
    if (!isSuccess) {
        //qDebug() << "iodevice open() error code: " << m_iodevice->errorString();
        throw(m_iodevice->errorString());
    }

    connect(m_iodevice, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}


// ---------------------------------------------------------------------------
GpsReceiver::~GpsReceiver()
{
    if (m_iodevice) {
        m_iodevice->close();
        delete(m_iodevice);
    }
}


// ---------------------------------------------------------------------------
void GpsReceiver::sendMessage(QString const& str)
{
    QByteArray msg = (((str.trimmed()).split('*'))[0]).toLocal8Bit();
    QByteArray sentence(msg);
    if (!sentence.startsWith('$')) sentence.push_front('$');

    unsigned int checksum = calculateChecksum(msg);

    char suffix[8];
    memset(suffix, 0, sizeof suffix);
    sprintf(suffix, "*%02X\r\n", checksum);

    sentence.append(suffix);

    // and write the sentence
    //qDebug() << sentence;
    int bytes_written = m_iodevice->write(sentence);

    if (bytes_written != sentence.length()) {
        //qDebug() << "bytes written not equal to sentence length.";
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
            //qDebug() << "iodevice read() failed. ";
        } else {
            QByteArray receivedLine(QByteArray(buf).trimmed());

            if (receivedLine[0] != '$' || !receivedLine.contains('*')) {
                //qDebug() << "recieved an incomplete line.";
            } else if (!verifyChecksum(receivedLine)) {
                //qDebug() << "recieved a line of garbage.";
            } else {

                emit nmeaSentence(QString(buf));
            }
        }
    }
}


// ---------------------------------------------------------------------------
unsigned int calculateChecksum(QByteArray const& message)
{
    unsigned int sum = 0;

    // iterate over the bytes of the message part and sum up the bytes.
    QByteArray::const_iterator iter = message.begin();
    if (message.at(0) == '$') {
        ++iter; // skip the '$' at the beginning.
    }
    while (iter != message.end()) {
        sum ^= *iter++;
    }
    return sum;
}

// ---------------------------------------------------------------------------
int verifyChecksum(QByteArray receivedSentence)
{
    int isGood;
    unsigned int calculated_sum; // sum of the data bytes in the message
    unsigned int checksum;
    bool isSuccess;


    // separate the message part from the checksum part
    QList<QByteArray> parts = receivedSentence.split('*');

    // calculate the checksum of the message part
    QByteArray message(parts[0]);
    calculated_sum = calculateChecksum(message);

    // get the received checksum value from the end of the sentence
    checksum = parts[1].toUInt(&isSuccess, 16);

    isGood = isSuccess && (calculated_sum == checksum);

    return isGood;
}

