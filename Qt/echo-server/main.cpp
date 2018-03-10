#include <QCoreApplication>
#include <QtCore>


#include "server.h"


int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    Server server(7000, &app);
    QObject::connect(&server, SIGNAL(quit()), &app, SLOT(quit()));
    int rc = app.exec();
    return rc;
}

