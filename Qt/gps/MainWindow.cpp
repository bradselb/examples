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

    QObject::connect(m_decoder, SIGNAL(updateDate(QDate const&)), m_display, SLOT(setDate(QDate const&)));
    QObject::connect(m_decoder, SIGNAL(updateTime(QTime const&)), m_display, SLOT(setTime(QTime const&)));

    QObject::connect(m_decoder, SIGNAL(updateLatitude(double)), m_display, SLOT(setLatitude(double)));
    QObject::connect(m_decoder, SIGNAL(updateLongitude(double)), m_display, SLOT(setLongitude(double)));
    QObject::connect(m_decoder, SIGNAL(updateAltitude(double)), m_display, SLOT(setAltitude(double)));

    QObject::connect(m_decoder, SIGNAL(updateFixQuality(int)), m_display, SLOT(setFixQuality(int)));
    QObject::connect(m_decoder, SIGNAL(updateFixStatus(QChar const&)), m_display, SLOT(setFixStatus(QChar const&)));
    QObject::connect(m_decoder, SIGNAL(updateFixMode(QChar const&)), m_display, SLOT(setFixMode(QChar const&)));

    QObject::connect(m_decoder, SIGNAL(updatePdop(double)), m_display, SLOT(setPdop(double)));
    QObject::connect(m_decoder, SIGNAL(updateHdop(double)), m_display, SLOT(setHdop(double)));
    QObject::connect(m_decoder, SIGNAL(updateVdop(double)), m_display, SLOT(setVdop(double)));

    QObject::connect(m_decoder, SIGNAL(updateSatsInUse(int)), m_display, SLOT(setSatsInUse(int)));
    QObject::connect(m_decoder, SIGNAL(updateGloSatsInView(int)), m_display, SLOT(setGloSatsInView(int)));
    QObject::connect(m_decoder, SIGNAL(updateGpsSatsInView(int)), m_display, SLOT(setGpsSatsInView(int)));

    QObject::connect(m_decoder, SIGNAL(updateDirectionOfTravel(double)), m_display, SLOT(setDirectionOfTravel(double)));
    QObject::connect(m_decoder, SIGNAL(updateSpeedOfTravelKmPerHr(double)), m_display, SLOT(setSpeedOfTravelKmPerHr(double)));

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
