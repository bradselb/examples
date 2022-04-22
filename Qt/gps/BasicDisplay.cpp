#include "BasicDisplay.h"
#include "ui_BasicDisplay.h"

#include <QObject>
#include <QElapsedTimer>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>

#include <QDebug>

// ---------------------------------------------------------------------------
BasicDisplay::BasicDisplay(QWidget* parent)
  : QWidget(parent)
  , m_elapsedtime(0), m_datetime(0)
  , m_latitude(0.0), m_longitude(0.0), m_altitude(0.0)
  , m_glinview(0), m_gpinview(0), m_gnsinuse(0)
  , m_fixquality(-1), m_fixstatus(QChar('-').cell()), m_fixmode(QChar('-').cell())
{
    m_ui = new Ui::BasicDisplay;
    m_ui->setupUi(this);

    m_elapsedtime = new QElapsedTimer();
    m_elapsedtime->start();

    m_datetime = new QDateTime();
    m_datetime->setTimeZone(QTimeZone(0)); // GPS time is always UTC
    m_datetime->setDate(QDate(2000,0,0));

    m_ui->latitude->setText("-99.999999");
    m_ui->longitude->setText("-999.999999");
}

// ---------------------------------------------------------------------------
BasicDisplay::~BasicDisplay()
{
    delete m_datetime;
    delete m_elapsedtime;
    delete m_ui;
}

// ---------------------------------------------------------------------------
void BasicDisplay::setTime(QTime const& t)
{
    m_datetime->setTime(t);
    this->setDateTime();
}

// ---------------------------------------------------------------------------
void BasicDisplay::setDate(QDate const& date)
{
    m_datetime->setDate(date);
    this->setDateTime();
}

// ---------------------------------------------------------------------------
void BasicDisplay::setDateTime()
{
    m_ui->datetime->setText(m_datetime->toLocalTime().toString("ddd, dd-MMM-yyyy  hh:mm:ss a"));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setLatitude(double lat)
{
    m_latitude = lat;
    m_ui->latitude->setText(QString("%1").arg(m_latitude,0,'f',6));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setLongitude(double lon)
{
    m_longitude = lon;
    m_ui->longitude->setText(QString("%1").arg(m_longitude,0,'f',6));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setAltitude(double alt)
{
    m_altitude = alt;
    m_ui->altitude->setText(QString("%1").arg(m_altitude,0,'f',1));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setFixQuality(int k)
{
    if (m_fixquality != k) {
        float elapsedtime = m_elapsedtime->elapsed()/1000.0;
        qDebug() << "Fix quality transitioned from" << m_fixquality << "to" << k << "at" << elapsedtime << "seconds";
        m_fixquality = k;
    }
    m_ui->fixquality->setText(QString("%1").arg(m_fixquality));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setFixStatus(QChar const& status)
{
    if (m_fixstatus !=  status.cell()) {
        float elapsedtime = m_elapsedtime->elapsed() / 1000.0;
        qDebug() << "Fix status transitioned from" << QChar(m_fixstatus) << "to" << status << "at" << elapsedtime << "seconds";
        m_fixstatus = status.cell();
    }
    m_ui->fixstatus->setText(status);
}

// ---------------------------------------------------------------------------
void BasicDisplay::setFixMode(QChar const& mode)
{
    if (m_fixmode != mode.cell()) {
        float elapsedtime = m_elapsedtime->elapsed() / 1000.0;
        qDebug() << "Fix mode transitioned from" << QChar(m_fixmode) << "to" << mode << "at" << elapsedtime << "seconds";
        m_fixmode = mode.cell();
    }
    m_ui->fixmode->setText(mode);
}

// ---------------------------------------------------------------------------
void BasicDisplay::setPdop(double pdop)
{
    m_ui->pdop->setText(QString("%1").arg(pdop, 0, 'f', 2));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setHdop(double hdop)
{
    m_ui->hdop->setText(QString("%1").arg(hdop, 0, 'f', 2));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setVdop(double vdop)
{
    m_ui->vdop->setText(QString("%1").arg(vdop, 0, 'f', 2));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setSatsInUse(int n)
{
    if (n != m_gnsinuse) {
        float elapsedtime = m_elapsedtime->elapsed() / 1000.0;
        qDebug() << "GNSS Satellites in use changed from" << m_gnsinuse  << "to" << n << "at" << elapsedtime << "seconds";
        m_gnsinuse = n;
    }
    m_ui->inuse->setText(QString("%1").arg(n));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setGloSatsInView(int n)
{
    if (n != m_glinview) {
        float elapsedtime = m_elapsedtime->elapsed() / 1000.0;
        qDebug() << "GLONASS Satellites in view changed from" << m_glinview  << "to" << n << "at" << elapsedtime << "seconds";
        m_glinview = n;
    }
    m_ui->inview->setText(QString("%1").arg(m_gpinview + m_glinview));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setGpsSatsInView(int n)
{
    if (n != m_gpinview) {
        float elapsedtime = m_elapsedtime->elapsed() / 1000.0;
        qDebug() << "GPS Satellites in view changed from" << m_gpinview  << "to" << n << "at" << elapsedtime << "seconds";
        m_gpinview = n;
    }
    m_ui->inview->setText(QString("%1").arg(m_gpinview + m_glinview));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setDirectionOfTravel(double direction)
{
    //QString value = QString("%1").arg(direction);
    //int n = 1 + value.indexOf('.');// index of first digit to right of the decimal point.
    //++n;// position of (not index of) first digit to right of the decimal point.
    //m_ui->direction->setText(QString(value.left(n)));
    m_ui->direction->setText(QString("%1").arg(direction,0,'f',0));
}

// ---------------------------------------------------------------------------
void BasicDisplay::setSpeedOfTravelKmPerHr(double speed)
{
    m_ui->speed->setText(QString("%1").arg(speed,0,'f',1));
}

