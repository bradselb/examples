#include "GpsReceiver.h"
#include "checksum.h"

#include <QObject>
#include <QIODevice>

#include <QDebug>


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
            if (!verify_checksum(buf)) {
                qDebug() << "recieved a line of garbage.";
            } else {

                QString s(buf);  // this function should emit a signal containing string, s and be done. 



                QStringList parts = s.split('*');
                QString message = parts[0].remove('$');
                QString checksum = parts[1];

                qDebug() << message << checksum;

                QStringList tokens = message.split(',');

                if (tokens[0] == QString("GPGGA")) {
                    ++gga_count;
                }
            }


        } else {
            qDebug() << "port read() failed. ";
        }
    }
    if (gga_count > 9) {
        emit quit();
    }
}
