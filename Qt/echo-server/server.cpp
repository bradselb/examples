#include "server.h"

#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QList>


Server::Server(quint16 port, QObject* parent)
: QObject(parent), m_tcpServer(0), m_clients()
{

    m_tcpServer = new QTcpServer(this);
    if (m_tcpServer) {
        m_tcpServer->setMaxPendingConnections(5);
        m_tcpServer->listen(QHostAddress::Any, port);
    }
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(handleConnection()));
}

Server::~Server()
{
    if (m_tcpServer) {
        m_tcpServer->close();
        delete m_tcpServer;
    }
}

//    quint64 byteCount;

void Server::handleConnection()
{
    QTcpSocket* client;
    client = m_tcpServer->nextPendingConnection();
    connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnect()));
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    m_clients.push_back(client);
    return;
}


void Server::onReadyRead()
{
    char buf[1024];
    QTcpSocket* client;

    for (int i=0; i<m_clients.count(); ++i) {
        client = m_clients.at(i);
        while (client->canReadLine()) {
            int length = client->readLine(buf, sizeof buf);
            if (length > 0) {
                client->write(buf); // just echo it back.
                QString cmd =  QString(buf) ;
                if (cmd.startsWith("quit", Qt::CaseInsensitive)) {
                    emit quit();
                }
            }
        }
    }
    return;
}


void Server::onClientDisconnect()
{
    QTcpSocket* client;
    for (int i=0; i<m_clients.count(); ++i) {
        if (m_clients.at(i)->state() != QAbstractSocket::ConnectedState) {
            // found one that is not connected...
            client = m_clients.takeAt(i); // removes it form the container.
            client->disconnect();
            client->deleteLater();
        }
    }
}



