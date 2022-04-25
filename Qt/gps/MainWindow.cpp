#include "MainWindow.h"
#include "BasicDisplay.h"
#include "MessageDecoder.h"
#include "GpsReceiver.h"

#include <QSerialPort>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>


MainWindow::MainWindow()
{
    m_display = new BasicDisplay();
    this->setCentralWidget(m_display);
    this->setMinimumSize(400,250);
    this->setMaximumSize(400,500);


    MessageDecoder* m_decoder = new MessageDecoder(this);

    QObject::connect(m_decoder, SIGNAL(date(QDate const&)), m_display, SLOT(onDate(QDate const&)));
    QObject::connect(m_decoder, SIGNAL(time(QTime const&)), m_display, SLOT(onTime(QTime const&)));

    QObject::connect(m_decoder, SIGNAL(latitude(double)), m_display, SLOT(onLatitude(double)));
    QObject::connect(m_decoder, SIGNAL(longitude(double)), m_display, SLOT(onLongitude(double)));
    QObject::connect(m_decoder, SIGNAL(altitude(double)), m_display, SLOT(onAltitude(double)));

    QObject::connect(m_decoder, SIGNAL(fixQuality(int)), m_display, SLOT(onFixQuality(int)));
    QObject::connect(m_decoder, SIGNAL(fixStatus(QChar const&)), m_display, SLOT(onFixStatus(QChar const&)));
    QObject::connect(m_decoder, SIGNAL(fixMode(QChar const&)), m_display, SLOT(onFixMode(QChar const&)));

    QObject::connect(m_decoder, SIGNAL(pdop(double)), m_display, SLOT(onPdop(double)));
    QObject::connect(m_decoder, SIGNAL(hdop(double)), m_display, SLOT(onHdop(double)));
    QObject::connect(m_decoder, SIGNAL(vdop(double)), m_display, SLOT(onVdop(double)));

    QObject::connect(m_decoder, SIGNAL(satsInUse(int)), m_display, SLOT(onSatsInUse(int)));
    QObject::connect(m_decoder, SIGNAL(gloSatsInView(int)), m_display, SLOT(onGloSatsInView(int)));
    QObject::connect(m_decoder, SIGNAL(gpsSatsInView(int)), m_display, SLOT(onGpsSatsInView(int)));

    QObject::connect(m_decoder, SIGNAL(directionOfTravel(double)), m_display, SLOT(onDirectionOfTravel(double)));
    QObject::connect(m_decoder, SIGNAL(speedOfTravelKmPerHr(double)), m_display, SLOT(onSpeedOfTravelKmPerHr(double)));

    QObject::connect(m_decoder, SIGNAL(proprietaryMessageReceived(QString const&)), m_display, SLOT(onProprietaryMessageReceived(QString const&)));
    //QObject::connect(m_decoder, SIGNAL(), m_display, SLOT());

    QSerialPort* m_serialport = new QSerialPort("/dev/ttyUSB0");
    m_serialport->setBaudRate(QSerialPort::Baud9600);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setStopBits(QSerialPort::OneStop);

    GpsReceiver* gps = new GpsReceiver(m_serialport, this);

    QObject::connect(gps, SIGNAL(nmeaSentence(QString const&)), m_decoder, SLOT(decodeNmeaSentence(QString const&)));
    QObject::connect(m_display, SIGNAL(sendMessage(QString const&)), gps, SLOT(sendMessage(QString const&)));

};
