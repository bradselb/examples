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
    m_sock = new QTcpSocket(this);

    m_buf = new char[m_bufsize];

    if (m_sock) {
        connect(m_sock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    }
}


// --------------------------------------------------------------------------
Client::~Client()
{
    delete[] m_buf;
}


// --------------------------------------------------------------------------
void Client::connectToHost(QString const& name, int port)
{
        m_sock->connectToHost(name, quint16(port));
        m_timerId = startTimer(500); // milli-seconds.
}


// --------------------------------------------------------------------------
void Client::onReadyRead()
{
    int byte_count = 0;

    while (m_sock && m_sock->bytesAvailable())
    {
        memset(m_buf, 0, m_bufsize);
        qint64 msglen = m_sock->read(m_buf, m_bufsize);
        byte_count += msglen;
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
    static const char* messages[] = {"Hello", "Nice to meet you", "good bye"};
    const int msg_count = sizeof messages / sizeof messages[0];

    if (event->timerId() != m_timerId) {
        // spurious?
        return;
    }

    if (!m_sock) {
        emit bailout();
    }
    else if (i < msg_count) {
        QByteArray message;
        message.append(QString("%1\n").arg(messages[i]));
        m_sock->write(message);
        ++i;
    }
#if 0
// this is not necessary. 
    else if (msg_count == i) {
        QByteArray message;
        message.append("bye\n");
        m_sock->write(message);
        ++i;
    }
#endif 
    else {
        killTimer(m_timerId);
        m_sock->disconnectFromHost();
        m_sock->close();
        m_sock->deleteLater();

        //QCoreApplication* parent = dynamic_cast<QCoreApplication* > (this->parent());
        //if (parent) parent->quit();

        emit bailout();
    }
}


