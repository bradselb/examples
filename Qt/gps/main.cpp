#include <QtCore>
#include <QCoreApplication>
//#include <QShortcut>
//#include <QKeySequence>


#include "GpsReceiver.h"


int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);


    GpsReceiver* gps = new GpsReceiver(&app);
    QObject::connect(gps, SIGNAL(quit()), &app, SLOT(quit()));

    int rc = app.exec();
    return rc;
}

