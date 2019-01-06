#include "GpsReceiver.h"

#include <QObject>
#include <QSerialPort>
#include <QIODevice>

#include <QDebug>


GpsReceiver::GpsReceiver(QObject* parent) : QObject(parent),m_port(0)
{
    m_port = new QSerialPort("/dev/ttyUSB0");
    m_port->setBaudRate(QSerialPort::Baud9600);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    bool isSuccess = m_port->open(QIODevice::ReadOnly);
    if (!isSuccess) {
        qDebug() << "port open() error code: " << m_port->error();
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
    char buf[1024];
    int length;
    static int gga_count = 0;

    if (m_port->canReadLine()) {
        length = m_port->read(buf, -1 + sizeof buf);
        if (length > 0) {
            buf[length] = 0;
            int i = length - 1;
            while (buf[i] == '\r' || buf[i] == '\n') {
                buf[i--] = 0;
            }

            //qDebug() << buf;


            // factor this stuff out to its own function.
            QString s(buf);
            //s = s.remove('\r').remove('\n');
            QStringList parts = s.split('*');
            QString message = parts[0];
            QString checksum = parts[1];
            // verify checksum
            QStringList tokens = message.split(',');

            qDebug() << tokens;


            if (tokens[0] == QString("$GPGGA")) {
                ++gga_count;
            }



        } else {
            qDebug() << "port read() failed. ";
        }
    }
    if (gga_count > 9) {
        emit quit();
    }
}


