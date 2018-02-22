#if !defined SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>

class QTcpServer;
class QTcpSocket;

class Server : public QObject
{
  Q_OBJECT

  public:
    Server(quint16 port=7000, QObject* parent=0);
    ~Server();

  signals:
    void quit();

  private slots:
    void handleConnection();
    void onReadyRead();
    void onClientDisconnect();

  private:
    QTcpServer* m_tcpServer;
    QList<QTcpSocket*> m_clients;
};


#endif //defined SERVER_H

