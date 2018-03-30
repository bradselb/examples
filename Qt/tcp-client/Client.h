#ifndef MY_UDP_CLIENT_H
#define MY_UDP_CLIENT_H

#include <QObject>

class QString;
class QTcpSocket;
class QTimerEvent;

class Client: public QObject
{
    Q_OBJECT

    signals:
        void bailout();

    public:
        Client(QObject* parent=0);
        ~Client();

        void connectToHost(QString const& name, int port);

    public slots:
        void onReadyRead();

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        QTcpSocket* m_sock;
        char* m_buf;
        const int m_bufsize;
        int m_timerId;
};

#endif

