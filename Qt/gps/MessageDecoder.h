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
        void updateDate(QDate const&); // RMC
        void updateTime(QTime const&); // RMC
        void updateLatitude(double); // RMC
        void updateLongitude(double); // RMC
        void updateAltitude(double); // GGA
        void updateSatsInUse(int); // GGA
        void updateGloSatsInView(int); // GNGSV
        void updateGpsSatsInView(int); // GPGSV
        void updateFixQuality(int); // GGA
        void updateFixStatus(QChar const&); // RMC
        void updateFixMode(QChar const&); // RMC
        void updatePdop(double); // GSA
        void updateHdop(double); // GSA
        void updateVdop(double); // GSA
        void updateDirectionOfTravel(double); // VTG
        void updateSpeedOfTravelKmPerHr(double); // VTG

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
