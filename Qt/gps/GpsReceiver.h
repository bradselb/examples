#if !defined GPSRECEIVER_H
#define GPSRECEIVER_H

#include <QObject>

class QIODevice;

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
        GpsReceiver(QIODevice* iodevice, QObject* parent=0);
        ~GpsReceiver();

    signals:
        void nmeaSentence(QString const&);

    public slots:
        void sendMessage(QString const&);

    private slots:
        void onReadyRead();

    private: // not implented
        GpsReceiver(GpsReceiver const&);
        GpsReceiver& operator=(GpsReceiver const&);

    private: // data
        QIODevice* m_iodevice;

};

#endif //!defined GPSRECEIVER_H
