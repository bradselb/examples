#if !defined GPSRECEIVER_H
#define GPSRECEIVER_H

#include <QObject>

class QIODevice;
class QSerialPortInfo;

// ---------------------------------------------------------------------------
// a class to represent the GNSS receiver
// it reads lines from an IO device,
// does some simple integrity checks and,
// for those lines that look like valid NMEA0183 sentences,
// it broadcasts the received NMEA 0183 sentence.
class GpsReceiver : public QObject
{
    Q_OBJECT

    public:
        GpsReceiver(QObject* parent=0);
        ~GpsReceiver();

    signals:
        void nmeaSentence(QString const&);
        void messageSent(QString const&);

    public slots:
        void onSendMessage(QString const&);
        void onSerialPortSelected(QSerialPortInfo const&);

    private slots:
        void onReadyRead();

    private: // not implented
        GpsReceiver(GpsReceiver const&);
        GpsReceiver& operator=(GpsReceiver const&);

    private: // data
        QIODevice* m_iodevice;

};

#endif //!defined GPSRECEIVER_H
