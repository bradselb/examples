#if !defined MESSAGEDECODER_H
#define MESSAGEDECODER_H

#include <QObject>

class QIODevice;

// ---------------------------------------------------------------------------
// Decode NMEA 0183 message strings.
// syntactic sugar ('$', "*" and checksum) and broadcasts the message body
class MessageDecoder : public QObject
{
    Q_OBJECT

    public:
        MessageDecoder(QObject* parent=0);
        ~MessageDecoder();

    signals:
        void date(QDate const&); // RMC
        void time(QTime const&); // RMC
        void latitude(double); // RMC
        void longitude(double); // RMC
        void altitude(double); // GGA
        void satsInUse(int); // GGA
        void gloSatsInView(int); // GNGSV
        void gpsSatsInView(int); // GPGSV
        void fixQuality(int); // GGA
        void fixStatus(QChar const&); // RMC
        void fixMode(QChar const&); // RMC
        void pdop(double); // GSA
        void hdop(double); // GSA
        void vdop(double); // GSA
        void directionOfTravel(double); // VTG
        void speedOfTravelKmPerHr(double); // VTG

        void proprietaryMessageReceived(QString const&);


    public slots:
        void decodeNmeaSentence(QString const&);

    private: // functions
        int decodeGGA(QStringList const& tokens);
        int decodeRMC(QStringList const& tokens);

    private: // not implented
        MessageDecoder(MessageDecoder const&);
        MessageDecoder& operator=(MessageDecoder const&);

    private: // data

};

#endif //!defined MESSAGEDECODER_H
