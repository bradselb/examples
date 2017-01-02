#include <QApplication>
#include <QtCore>

#include <stdlib.h>
#include <stddef.h>

#include "server.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Server server;
    server.show();
    server.exec();
    return 0;
}

