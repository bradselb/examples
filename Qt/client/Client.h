#ifndef MY_UDP_CLIENT_H
#define MY_UDP_CLIENT_H


#include <QObject>
//#include <QUdpSocket>
class QUdpSocket;

class Client: public QObject
{
    Q_OBJECT

    public:
        Client(QObject* parent=0);
        ~Client();

    public slots:

    private:
        QUdpSocket* m_sock;
};

#endif

