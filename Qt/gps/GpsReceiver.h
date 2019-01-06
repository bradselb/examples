#if !defined GPSRECEIVER_H
#define GPSRECEIVER_H

#include <QObject>

class QSerialPort;

class GpsReceiver : public QObject
{

    Q_OBJECT

    public:
        GpsReceiver(QObject* parent=0);
        ~GpsReceiver();

    signals:
        void quit();

    public slots:
        void onReadyRead();


    private: // not impleented
        GpsReceiver(GpsReceiver const&);
        GpsReceiver& operator=(GpsReceiver const&);

    private:
        QSerialPort* m_port;

};

#endif //!defined GPSRECEIVER_H
