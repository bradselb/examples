#include "server.h"
#include "XmlHandler.h"

#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QList>
#include <QDebug>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

#include <stdlib.h>
#include <string.h> // memset()
#include <stdio.h> //popen(), pclose()

Server::Server(quint16 port, QObject* parent)
: QObject(parent), m_tcpServer(0), m_clients()
{

    m_tcpServer = new QTcpServer(this);
    if (m_tcpServer) {
        m_tcpServer->setMaxPendingConnections(5);
        m_tcpServer->listen(QHostAddress::Any, port);
        qDebug() << "TCP/IP server listening on port:" << m_tcpServer->serverPort();
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
    qDebug() << "client connected from" << client->peerAddress().toString() << "port:" << client->peerPort();
    return;
}


void Server::onReadyRead()
{
    char buf[1024];

    for (int i=0; i<m_clients.count(); ++i) {
        QTcpSocket* client; // inherits QIODevice
        client = m_clients.at(i);
        QXmlInputSource myXmlInputSource(client);
        QXmlSimpleReader myXmlReader;
        XmlHandler myXmlHandler;

        myXmlReader.setContentHandler(&myXmlHandler);
        myXmlReader.setErrorHandler(&myXmlHandler);

        bool isParseSuccess;
        isParseSuccess = myXmlReader.parse(&myXmlInputSource);
        qDebug() << "is XML parse successful?" << isParseSuccess;
        client->write("ok"); 

#if 0
        while (client->canReadLine()) {
            int length = client->readLine(buf, sizeof buf);
            if (length > 0) {
                //client->write(buf); // echo it back.
                QString cmd =  QString(buf) ;
                cmd.remove("\n");
    qDebug() << cmd << "from:" << client->peerAddress().toString() << client->peerPort();
                if (cmd.startsWith("quit", Qt::CaseInsensitive)) {
                    emit quit();
                } else if (cmd.startsWith("bye", Qt::CaseInsensitive)) {
                    client->disconnectFromHost();
                } else {
                    FILE* f = popen(buf, "r");  // throw the command out to the shell and...
                    memset(buf, 0, sizeof buf); // read back whatever the command writes to stdout
                    while (0 < fgets(buf, sizeof buf, f)) {
                        client->write(buf); 
                    }
                    pclose(f);
                    //client->write("\nok >");
                }
            }
        }
#endif 
    } // for 
    return;
}


void Server::onClientDisconnect()
{
    QTcpSocket* client;
    for (int i=0; i<m_clients.count(); ++i) {
        if (m_clients.at(i)->state() != QAbstractSocket::ConnectedState) {
            // found one that is not connected...
            client = m_clients.takeAt(i); // removes it form the container.
    qDebug() << "client disconnected:" << client->peerName() << client->peerAddress() << client->peerPort();
            client->disconnect();
            client->deleteLater();
        }
    }
}



