#if !defined TRACKLOGGER_H
#define TRACKLOGGER_H

#include <QObject>
#include <QString>

#include <time.h> // time_t

class TrackLogger : public QObject
{
    Q_OBJECT

    public:
        TrackLogger(QObject* parent=0);
        ~TrackLogger();

    public slots:
        void onEnable(int);
        void onLogIntervalChange(QString const&);
        void onGGA(int hours, int minutes, int seconds, double lat, double lon, int fixquality, int sats, double hdop, double altitude, double geoid);
        void onRMC(int hours, int minutes, int seconds, int fixstatus, double lat, double lon, int day, int month, int year, int fixmode);

    private: // data
        QString m_filename;
        double m_altitude; // saved from previous GGA message
        time_t m_prev;
        int m_activeSats; // also from GGA
        int m_interval;
        int m_enable;

};

#endif //!defined TRACKLOGGER_H
