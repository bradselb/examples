#include "Client.h"

#include <QtCore>
#include <QtNetwork>
#include <QDebug>


// --------------------------------------------------------------------------
Client::Client(QObject* parent)
   : QObject(parent)
   , m_sock(0)
   , m_buf(0)
   , m_bufsize(4096)
   , m_timerId(0)
{
    m_sock = new QUdpSocket(this);

    m_buf = new char[m_bufsize];

    if (m_sock) {
        connect(m_sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    }
}


// --------------------------------------------------------------------------
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


// --------------------------------------------------------------------------
void Client::connectToHost(QString const& name, int port)
{
        m_sock->connectToHost(name, quint16(port));
        m_timerId = startTimer(3000); // milli-seconds.
}


// --------------------------------------------------------------------------
void Client::onReadyRead()
{
    while (m_sock->hasPendingDatagrams()) 
    {
        memset(m_buf, 0, m_bufsize);
        qint64 msglen = m_sock->read(m_buf, m_bufsize);

        if (msglen > 0) {
            qDebug() << m_buf;
        }
    }
}


// --------------------------------------------------------------------------
// send a message periodically
void Client::timerEvent(QTimerEvent* event)
{
    static int i = 0;

    if (event->timerId() != m_timerId) {
        // spurious?
        return;
    }

    QByteArray datagram;
    datagram.append(QString("< %1 >").arg(i));

    if (m_sock) { //&& m_remoteHostInfo && !m_remoteHostInfo->addresses().isEmpty()) {
        //QHostAddress addr = m_remoteHostInfo->addresses().first();;
        //quint16 port = m_remoteHostPort;

        qDebug() << "writing datagram, i:" << i;
        //m_sock->writeDatagram(datagram, addr, port);
        m_sock->write(datagram);
        ++i;
    }
}


