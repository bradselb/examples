#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "BasicDisplay.h"
#include "MessageDecoder.h"
#include "GpsReceiver.h"
#include "Logger.h"
#include "SerialPortSelect.h"

#include <QMainWindow>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    BasicDisplay* display = new BasicDisplay();
    this->setCentralWidget(display);
    this->setMaximumSize(640,768);

    // ----------------------------------------------------------------------
    MessageDecoder* decoder = new MessageDecoder(this);

    connect(decoder, SIGNAL(date(QDate const&)), display, SLOT(onDate(QDate const&)));
    connect(decoder, SIGNAL(time(QTime const&)), display, SLOT(onTime(QTime const&)));

    connect(decoder, SIGNAL(latitude(double)), display, SLOT(onLatitude(double)));
    connect(decoder, SIGNAL(longitude(double)), display, SLOT(onLongitude(double)));
    connect(decoder, SIGNAL(altitude(double)), display, SLOT(onAltitude(double)));

    connect(decoder, SIGNAL(fixQuality(int)), display, SLOT(onFixQuality(int)));
    connect(decoder, SIGNAL(fixStatus(QChar const&)), display, SLOT(onFixStatus(QChar const&)));
    connect(decoder, SIGNAL(fixMode(QChar const&)), display, SLOT(onFixMode(QChar const&)));

    connect(decoder, SIGNAL(pdop(double)), display, SLOT(onPdop(double)));
    connect(decoder, SIGNAL(hdop(double)), display, SLOT(onHdop(double)));
    connect(decoder, SIGNAL(vdop(double)), display, SLOT(onVdop(double)));

    connect(decoder, SIGNAL(satsInUse(int)), display, SLOT(onSatsInUse(int)));
    connect(decoder, SIGNAL(gloSatsInView(int)), display, SLOT(onGloSatsInView(int)));
    connect(decoder, SIGNAL(gpsSatsInView(int)), display, SLOT(onGpsSatsInView(int)));

    connect(decoder, SIGNAL(directionOfTravel(double)), display, SLOT(onDirectionOfTravel(double)));
    connect(decoder, SIGNAL(speedOfTravelKmPerHr(double)), display, SLOT(onSpeedOfTravelKmPerHr(double)));

    connect(decoder, SIGNAL(proprietaryMessageReceived(QString const&)), display, SLOT(onProprietaryMessage(QString const&)));
    //connect(decoder, SIGNAL(), display, SLOT());

    // ----------------------------------------------------------------------
    GpsReceiver* gps = new GpsReceiver(this);
    connect(gps, SIGNAL(nmeaSentence(QString const&)), decoder, SLOT(decodeNmeaSentence(QString const&)));
    connect(display, SIGNAL(sendMessage(QString const&)), gps, SLOT(onSendMessage(QString const&)));
    connect(gps, SIGNAL(messageSent(QString const&)), display, SLOT(onProprietaryMessage(QString const&)));

    // ----------------------------------------------------------------------
    TrackLogger* logger = new TrackLogger(this);
    connect(decoder, SIGNAL(date(QDate const&)), logger, SLOT(onDate(QDate const&)));
    connect(decoder, SIGNAL(time(QTime const&)), logger, SLOT(onTime(QTime const&)));

    connect(decoder, SIGNAL(GGA(int,int,int,double,double,int,int,double,double,double)),
            logger,    SLOT(onGGA(int,int,int,double,double,int,int,double,double,double)));

    connect(decoder, SIGNAL(RMC(int,int,int,int,double,double,int,int,int,int)),
            logger,    SLOT(onRMC(int,int,int,int,double,double,int,int,int,int)));

    connect(display, SIGNAL(logIntervalChange(QString const&)), logger, SLOT(onLogIntervalChange(QString const&)));
    connect(display, SIGNAL(enableLogger(int)), logger, SLOT(onEnable(int)));

    // ----------------------------------------------------------------------
    SerialPortSelect* portselect = new SerialPortSelect(this);
    connect(portselect, SIGNAL(serialPortSelected(QSerialPortInfo const&)), gps, SLOT(onSerialPortSelected(QSerialPortInfo const&)));
    portselect->setModal(true);
    portselect->show(); // **DO NOT** call exec() in a constructor!

    statusBar()->showMessage("Ready");
};


// ---------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

// ---------------------------------------------------------------------------
void MainWindow::setStatus(QString const& message)
{
    statusBar()->showMessage(message);
}

