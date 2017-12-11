#include "Client.h"

#include <QtNetwork>
#include <QTimerEvent>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>


#include <iostream>
#include <fstream>

Client::Client(QObject* parent) : QObject(parent), m_sock(0), m_buf(0), m_bufsize(4096), m_timerId(0)
{
    m_sock = new QUdpSocket(this);

    m_buf = new char[m_bufsize];

    if (m_sock) {
        m_sock->bind(1735);
        m_timerId = startTimer(1000);
        connect(m_sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    }
}

Client::~Client()
{
    if (m_timerId) {
        killTimer(m_timerId);
    }

    if (m_sock) {
        m_sock->close();
    }

    delete[] m_buf;
}


void Client::onReadyRead()
{
    while (m_sock->hasPendingDatagrams()) {
        QHostAddress peerAddr;
        quint16 peerPort;

        memset(m_buf, 0, m_bufsize);
        qint64 msglen = m_sock->readDatagram(m_buf, m_bufsize, &peerAddr, &peerPort);

        if (msglen > 0) {
            qDebug() << "received" << msglen << "bytes from" << peerAddr.toString() << "port:" << peerPort;
            qDebug() << m_buf;
        }
    }
}



// send a message periodically
void Client::timerEvent(QTimerEvent* event)
{
    static int i = 0;
    QByteArray datagram;
    datagram.append(QString("< %1 >").arg(i++));

    QHostAddress addr("127.0.0.1");
    quint16 port = 1735;

    if (m_sock) {
        qDebug() << "writing datagram, i:" << i;
        m_sock->writeDatagram(datagram, addr, port);
    }

}


