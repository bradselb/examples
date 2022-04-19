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
        void updateAltitude(double);
        void updateLatitude(double);
        void updateLongitude(double);
        void updateHeading(double);
        void updateTime(QTime const&);
        void updateDate(QDate const&);
        void updateDateTime(QDateTime const&);
        void updateSatellitesUsed(int);
        void updateGloSatsInView(int);
        void updateGpsSatsInView(int);
        void updateFixQuality(int);
        void updateFixStatus(QString const&);
        void updateFixMode(QString const&);
        void updateHDOP(int);


    public slots:
        void decodeNmeaSentence(QString const&);


    private: // not implented
        MessageDecoder(MessageDecoder const&);
        MessageDecoder& operator=(MessageDecoder const&);

    private: // data

};

#endif //!defined MESSAGEDECODER_H
