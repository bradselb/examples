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
        void quit();

    public slots:
        void onReadyRead();


    private: // not impleented
        GpsReceiver(GpsReceiver const&);
        GpsReceiver& operator=(GpsReceiver const&);

    private:
        QIODevice* m_port;

};

#endif //!defined GPSRECEIVER_H
