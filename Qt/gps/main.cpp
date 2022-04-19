#include "BasicDisplay.h"
#include "MessageDecoder.h"
#include "GpsReceiver.h"

#include <QApplication>
#include <QSerialPort>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    BasicDisplay basicdisplay;

    MessageDecoder* decoder = new MessageDecoder(&basicdisplay);

    QObject::connect(decoder, SIGNAL(updateAltitude(double)), &basicdisplay, SLOT(setAltitude(double)));
    QObject::connect(decoder, SIGNAL(updateLatitude(double)), &basicdisplay, SLOT(setLatitude(double)));
    QObject::connect(decoder, SIGNAL(updateLongitude(double)), &basicdisplay, SLOT(setLongitude(double)));
    QObject::connect(decoder, SIGNAL(updateDate(QDate const&)), &basicdisplay, SLOT(setDate(QDate const&)));
    QObject::connect(decoder, SIGNAL(updateTime(QTime const&)), &basicdisplay, SLOT(setTime(QTime const&)));
    QObject::connect(decoder, SIGNAL(updateDateTime(QDateTime const&)), &basicdisplay, SLOT(setDateTime(QDateTime const&)));
    QObject::connect(decoder, SIGNAL(updateFixQuality(int)), &basicdisplay, SLOT(setFixQuality(int)));
    QObject::connect(decoder, SIGNAL(updateFixStatus(QString const&)), &basicdisplay, SLOT(setFixStatus(QString const&)));
    QObject::connect(decoder, SIGNAL(updateFixMode(QString const&)), &basicdisplay, SLOT(setFixMode(QString const&)));
    QObject::connect(decoder, SIGNAL(updateSatellitesUsed(int)), &basicdisplay, SLOT(setSatsInUse(int)));
    QObject::connect(decoder, SIGNAL(updateGloSatsInView(int)), &basicdisplay, SLOT(setGloSatsInView(int)));
    QObject::connect(decoder, SIGNAL(updateGpsSatsInView(int)), &basicdisplay, SLOT(setGpsSatsInView(int)));

    QSerialPort* serialport = new QSerialPort("/dev/ttyUSB0");
    serialport->setBaudRate(QSerialPort::Baud9600);
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setParity(QSerialPort::NoParity);
    serialport->setStopBits(QSerialPort::OneStop);

    GpsReceiver* gps = new GpsReceiver(serialport, &basicdisplay);

    QObject::connect(gps, SIGNAL(nmeaSentence(QString const&)), decoder, SLOT(decodeNmeaSentence(QString const&)));

    basicdisplay.show();

    return app.exec();
}

