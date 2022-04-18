#include "GpsReceiver.h"
#include "BasicDisplay.h"

//#include <QtCore>
//#include <QCoreApplication>
//#include <QIODevice>
#include <QApplication>
#include <QSerialPort>
#include <QDateTime>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    BasicDisplay* basicdisplay = new BasicDisplay();
    basicdisplay->show();

    QSerialPort* serialport = new QSerialPort("/dev/ttyUSB0");
    serialport->setBaudRate(QSerialPort::Baud9600);
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setParity(QSerialPort::NoParity);
    serialport->setStopBits(QSerialPort::OneStop);

    GpsReceiver* gps = new GpsReceiver(&app, serialport);

    QObject::connect(gps, SIGNAL(updateAltitude(double)), basicdisplay, SLOT(setAltitude(double)));
    QObject::connect(gps, SIGNAL(updateLatitude(double)), basicdisplay, SLOT(setLatitude(double)));
    QObject::connect(gps, SIGNAL(updateLongitude(double)), basicdisplay, SLOT(setLongitude(double)));
    QObject::connect(gps, SIGNAL(updateHeading(double)), basicdisplay, SLOT(setHeading(double)));
    QObject::connect(gps, SIGNAL(updateDate(QDate const&)), basicdisplay, SLOT(setDate(QDate const&)));
    QObject::connect(gps, SIGNAL(updateTime(QTime const&)), basicdisplay, SLOT(setTime(QTime const&)));
    QObject::connect(gps, SIGNAL(updateDateTime(QDateTime const&)), basicdisplay, SLOT(setDateTime(QDateTime const&)));
    QObject::connect(gps, SIGNAL(updateFixQuality(int)), basicdisplay, SLOT(setFixQuality(int)));
    QObject::connect(gps, SIGNAL(updateFixValid(QString const&)), basicdisplay, SLOT(setFixValid(QString const&)));
    QObject::connect(gps, SIGNAL(updateFixMode(QString const&)), basicdisplay, SLOT(setFixMode(QString const&)));
    QObject::connect(gps, SIGNAL(updateSatellitesUsed(int)), basicdisplay, SLOT(setSatsInUse(int)));
    QObject::connect(gps, SIGNAL(updateGlonasInView(int)), basicdisplay, SLOT(setGlonasInView(int)));
    QObject::connect(gps, SIGNAL(updateGpsSatInView(int)), basicdisplay, SLOT(setGpsSatInView(int)));
    QObject::connect(basicdisplay, SIGNAL(quit()), &app, SLOT(quit()));

    int rc = app.exec();
    return rc;
}

