#if !defined GPSRECEIVER_H
#define GPSRECEIVER_H

#include <QObject>

class QIODevice;

class GpsReceiver : public QObject
{

    Q_OBJECT

    public:
        GpsReceiver(QObject* parent, QIODevice* port);
        ~GpsReceiver();

    signals:
        void messageReceived(QString const&);
        void updateAltitude(double);
        void updateLatitude(double);
        void updateLongitude(double);
        void updateHeading(double);
        void updateTime(QTime const&);
        void updateDate(QDate const&);
        void updateDateTime(QDateTime const&);
        void updateSatellitesUsed(int);
        void updateGlonasInView(int);
        void updateGpsSatInView(int);
        void updateFixQuality(int);
        void updateFixValid(QString const&);
        void updateFixMode(QString const&);
        void updateHDOP(int);


    public slots:
        void onReadyRead();


    private: // not implented
        GpsReceiver(GpsReceiver const&);
        GpsReceiver& operator=(GpsReceiver const&);

    private:
        QIODevice* m_port;

};

#endif //!defined GPSRECEIVER_H
