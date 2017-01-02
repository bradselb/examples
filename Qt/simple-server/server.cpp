#include "server.h"

#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QPushButton>
#include <QLabel>

#include <stdio.h>

Server::Server(QWidget* parent, quint16 port)
: QDialog(parent), m_tcpServer(0)//, m_label(new QLabel), m_button(new QPushButton(tr("Quit")))
{
//    m_button->setAutoDefault(false);
//    m_button->show();

    m_tcpServer = new QTcpServer(this);
    if (m_tcpServer) {
        m_tcpServer->setMaxPendingConnections(5);
        m_tcpServer->listen(QHostAddress::Any, port);
    }
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(handleConnection()));
    fprintf(stderr, "Server constructed\n");
}

Server::~Server()
{
    if (m_tcpServer) {
        m_tcpServer->close();
        delete m_tcpServer;
    }
}

void Server::handleConnection()
{
    QTcpSocket* client;
    quint64 byteCount;
    char buf[1024];

    fprintf(stderr, "handleConnnection()\n");

    client = m_tcpServer->nextPendingConnection();
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    byteCount = client->readLine(buf, sizeof buf);
    fprintf(stderr, "handleConnnection(), byteCout: %lld\n", byteCount);
    if (byteCount != -1) {
        // a message has been received.
        //processMessage(buf);
        fprintf(stderr, "%s\n", buf);
//        m_label->setText(QString(buf));
//        m_label->show();
        client->write(buf);
    }

}
