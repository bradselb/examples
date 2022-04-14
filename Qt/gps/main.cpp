#include "GpsReceiver.h"

#include <QtCore>
#include <QCoreApplication>
#include <QIODevice>
#include <QSerialPort>



int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QSerialPort* serialport = new QSerialPort("/dev/ttyUSB0");
    serialport->setBaudRate(QSerialPort::Baud9600);
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setParity(QSerialPort::NoParity);
    serialport->setStopBits(QSerialPort::OneStop);

    GpsReceiver* gps = new GpsReceiver(&app, serialport);
    QObject::connect(gps, SIGNAL(quit()), &app, SLOT(quit()));

    int rc = app.exec();
    return rc;
}

