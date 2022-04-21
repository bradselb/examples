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
        void updateDate(QDate const&);
        void updateTime(QTime const&);
        void updateLatitude(double);
        void updateLongitude(double);
        void updateAltitude(double);
        void updateSatsInUse(int);
        void updateGloSatsInView(int);
        void updateGpsSatsInView(int);
        void updateFixQuality(int);
        void updateFixStatus(QChar const&);
        void updateFixMode(QChar const&);
        void updateHDOP(int);
        void updateDirectionOfTravel(double); // VTG
        void updateSpeedOfTravelKmPerHr(double); // VTG


    public slots:
        void decodeNmeaSentence(QString const&);


    private: // not implented
        MessageDecoder(MessageDecoder const&);
        MessageDecoder& operator=(MessageDecoder const&);

    private: // data

};

#endif //!defined MESSAGEDECODER_H
