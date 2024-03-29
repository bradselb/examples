#include "Logger.h"

#include <QDateTime>
#include <QTimeZone>

#include <time.h> // strftime(), struct tm
#include <string.h> // memset()
#include <stdio.h> // snprintf()


// ---------------------------------------------------------------------------
TrackLogger::TrackLogger(QObject* parent)
    : QObject(parent)
    , m_datetime(0)
    , m_filename("track.log")
    , m_altitude(0.0)
    , m_hdop(0.0)
    , m_prev(0)
    , m_activeSats(0)
    , m_fixQuality(0)
    , m_interval(0)
    , m_enable(0)
{
    m_datetime = new QDateTime();
    m_datetime->setTimeZone(QTimeZone(0)); // GPS time is always UTC
    m_datetime->setDate(QDate(2000,0,0));
}

// ---------------------------------------------------------------------------
TrackLogger::~TrackLogger()
{
    delete m_datetime;
}

// ---------------------------------------------------------------------------
void TrackLogger::onEnable(int enable)
{
    if (enable) {
        // create a new file name
        QDateTime localtime(m_datetime->toLocalTime());
        QString timestamp(localtime.toString("yyyy-MM-dd_hh.mm.sst"));
        m_filename = QString("gps_%1.log").arg(timestamp);
        m_enable = 1;
    } else {
        m_enable = 0;
    }
}

// ---------------------------------------------------------------------------
void TrackLogger::onLogIntervalChange(QString const& str)
{
    bool isConversionSuccess;
    int interval = str.toInt(&isConversionSuccess);
    if (isConversionSuccess) m_interval = interval;
}

// ---------------------------------------------------------------------------
void TrackLogger::onDate(QDate const& date)
{
    m_datetime->setDate(date);
}

// ---------------------------------------------------------------------------
void TrackLogger::onTime(QTime const& t)
{
    m_datetime->setTime(t);
}

// ---------------------------------------------------------------------------
void TrackLogger::onGGA(int, int, int, double, double, int fixquality, int sats, double hdop, double altitude, double)
//void TrackLogger::onGGA(int hours, int minutes, int seconds, double lat, double lon, int fixquality, int sats, double hdop, double altitude, double geoid)
{
    m_activeSats = sats;
    m_fixQuality = fixquality;
    m_altitude = altitude;
    m_hdop = hdop;
}

// ---------------------------------------------------------------------------
void TrackLogger::onRMC(int hours, int minutes, int seconds, int fixstatus, double lat, double lon, int day, int month, int year, int)
//void TrackLogger::onRMC(int hours, int minutes, int seconds, int fixstatus, double lat, double lon, int day, int month, int year, int fixmode)
{
    char buf[128];
    char timestamp_iso8601[24];
    struct tm t;
    time_t now;

    t.tm_sec = seconds;
    t.tm_min = minutes;
    t.tm_hour = hours;
    t.tm_mday = day;
    t.tm_mon = month - 1; // january --> 0;
    t.tm_year = year - 1900; // years since 1900
    t.tm_isdst = 0; // UTC is never dst.

    now = mktime(&t);

    if (now != (time_t)-1 && m_enable && m_interval>0)
    {
        if ((difftime(now, m_prev) >= m_interval) && (seconds % m_interval == 0) && (fixstatus == 'A'))
        {
            m_prev = now;

            //strftime(timestamp_iso8601, sizeof timestamp_iso8601, "%Y-%m-%dT%H:%M:%Sz", &t); // C89
            strftime(timestamp_iso8601, sizeof timestamp_iso8601, "%FT%Tz", &t); // C99

            memset(buf, 0, sizeof buf);
            snprintf(buf, sizeof buf, "%s,%1.6f,%1.6f,%1.1f,%1.2f,%d,%d", timestamp_iso8601, lat, lon, m_altitude, m_hdop, m_activeSats, m_fixQuality);

            FILE* f = fopen(m_filename.toStdString().c_str(), "a");
            if (f) fprintf(f, "%s\n", buf);
            fclose(f);
        }
    }
    else
    {
        ; // mktime() returned an error or logging not enabled or log interval is zero.
    }
}

