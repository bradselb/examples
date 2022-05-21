#if !defined MESSAGE_H
#define MESSAGE_H

#include <QTime>
//#include <QDate>
#include <QDateTime>
#include <QString>
#include <QList>

struct GGA
{
    QTime utc;
    double lat;
    double lon;
    int fix_quality; // 0-->no fix, 1-->GPS fix, 2-->DGPS fix
    int active_count;
    double hdop;
    double alt;
    double geoid_height;
};

struct GSA
{
    int fix_type; // 1-->none, 2-->2d, 3-->3d
    QList<int> prns;
    double pdop;
    double hdop;
    double vdop;
};


struct SatInfo
{
    int prn;
    int elev;
    int azim;
    int snr;
};

struct GSV
{
    int in_view_count;
    QList<struct SatInfo> descriptors;
};

struct RMC
{
    QDateTime date_time;
    QChar fix_status; // V-->no fix, A-->fix
    double lat;
    double lon;
    double speed_knots;
    double direction; // true
    QChar fix_mode; // N-->none, A-->autonomous, D-->differential, E-->Estimated
};

struct VTG
{
    double direction; // true
    double speed_knots;
    double speed_kph;
    QChar fix_mode; // N-->none, A-->autonomous, D-->differential, E-->Estimated
};

#endif //!defined MESSAGE_H
