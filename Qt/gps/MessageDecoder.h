#if !defined MESSAGEDECODER_H
#define MESSAGEDECODER_H

#include <QObject>

// ---------------------------------------------------------------------------
// Decode select NMEA 0183 sentences.
class MessageDecoder : public QObject
{
    Q_OBJECT

    public:
        MessageDecoder(QObject* parent=0);
        ~MessageDecoder();

    signals:
        void date(QDate const&); // RMC
        void time(QTime const&); // GGA, RMC
        void latitude(double); // RMC
        void longitude(double); // RMC
        void altitude(double); // GGA
        void satsInUse(int); // GGA
        void activeSatCount(int); // GSA
        void activeSatPRN(int); // GSA
        void gloSatsInView(int); // GNGSV
        void gpsSatsInView(int); // GPGSV
        //void satInView(int prn, int azim, int elev, int snr); // GSV
        void fixQuality(int); // GGA
        void fixStatus(QChar const&); // RMC
        void fixMode(QChar const&); // RMC
        void fixType(int); // GSA
        void pdop(double); // GSA
        void hdop(double); // GSA, GGA
        void vdop(double); // GSA
        void directionOfTravel(double); // VTG
        void speedOfTravelKmPerHr(double); // VTG

        void proprietaryMessageReceived(QString const&);

        void GGA(int hours, int minutes, int seconds, double lat, double lon, int fixquality, int sats, double hdop, double altitude, double geoid);

        //void RMC(int hours, int minutes, int seconds, int fixstatus, double lat, double lon, int day, int month, int year, int fixmode);
        void RMC(int,int,int,int,double,double,int,int,int,int);


    public slots:
        void decodeNmeaSentence(QString const&);

    private: // functions
        int decodeGGA(QStringList const& tokens);
        int decodeGSA(QStringList const& tokens);
        int decodeGSV(QStringList const& tokens);
        int decodeRMC(QStringList const& tokens);
        int decodeVTG(QStringList const& tokens);

    private: // not implented
        MessageDecoder(MessageDecoder const&);
        MessageDecoder& operator=(MessageDecoder const&);

    private: // data

};

#endif //!defined MESSAGEDECODER_H
