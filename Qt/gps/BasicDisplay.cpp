#include "BasicDisplay.h"
#include "ui_BasicDisplay.h"

#include <QObject>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>

BasicDisplay::BasicDisplay(QWidget* parent)
  : QWidget(parent)
  , m_elapsedtime(), m_datetime(0)
  , m_latitude(0.0), m_longitude(0.0)
  , m_altitude(0.0)
  , m_glinview(0), m_gpinview(0)
  , m_fixquality(0)
{
    m_elapsedtime.start();

    m_ui = new Ui::BasicDisplay;
    m_ui->setupUi(this);

    m_datetime = new QDateTime();
    m_datetime->setTimeZone(QTimeZone(0)); // GPS time is always UTC

    m_ui->inview->setText("--");
}

BasicDisplay::~BasicDisplay()
{
    delete m_datetime;
    delete m_ui;
}
void BasicDisplay::setTime(QTime const& t)
{
    m_datetime->setTime(t);
    this->setDateTime(*m_datetime);
    //m_ui->datetime->setText(m_datetime->toLocalTime().toString("ddd, dd-MMM-yyyy  hh:mm:ss a"));
}
void BasicDisplay::setDate(QDate const& date)
{
    m_datetime->setDate(date);
    this->setDateTime(*m_datetime);
}

void BasicDisplay::setDateTime(QDateTime const& dt)
{
    m_datetime->setTime(dt.time());
    m_datetime->setDate(dt.date());
    //m_datetime->setTimeZone(dt.timeZone());
    m_ui->datetime->setText(dt.toLocalTime().toString("ddd, dd-MMM-yyyy  hh:mm:ss a"));
}

void BasicDisplay::setLatitude(double lat)
{
    m_latitude = lat;
    m_ui->latitude->setText(QString("%1").arg(m_latitude, 0, 'f', -6));
}

void BasicDisplay::setLongitude(double lon)
{
    m_longitude = lon;
    m_ui->longitude->setText(QString("%1").arg(m_longitude, 0, 'f', -6));
}

void BasicDisplay::setAltitude(double alt)
{
    m_altitude = alt;
    m_ui->altitude->setText(QString("%1").arg(m_altitude, 0, 'g', -1));
}

void BasicDisplay::setFixQuality(int k)
{
    if (0 == m_fixquality) {
        // show elapsed time to first fix. Once fix quality != 0 stop showing elapsed time.
        // not elapsed time is in milliseconds so, divide by 1000
        float t_seconds = m_elapsedtime.elapsed()/1000.0;
        if (t_seconds < 0.0)
            m_ui->timetofirstfix->setText(QString("0.%1").arg(t_seconds));
        else
            m_ui->timetofirstfix->setText(QString("%1").arg(t_seconds));
    }
    m_fixquality = k;
    m_ui->fixquality->setText(QString("%1").arg(m_fixquality));
}

void BasicDisplay::setFixStatus(QString const& status)
{
    m_ui->fixstatus->setText(status);
}

void BasicDisplay::setFixMode(QString const& s)
{
    m_ui->fixmode->setText(s);
}

void BasicDisplay::setSatsInUse(int n)
{
    m_ui->inuse->setText(QString("%1").arg(n));
}

void BasicDisplay::setGloSatsInView(int n)
{
    m_glinview = n;
    m_ui->inview->setText(QString("%1").arg(m_gpinview + m_glinview));
}

void BasicDisplay::setGpsSatsInView(int n)
{
    m_gpinview = n;
    m_ui->inview->setText(QString("%1").arg(m_gpinview + m_glinview));
}

