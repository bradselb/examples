#if !defined BASICDISPLAY_H
#define BASICDISPLAY_H

#include <QWidget>
class QElapsedTimer;

namespace Ui {class BasicDisplay;}


class BasicDisplay : public QWidget
{
    Q_OBJECT

    public:
        BasicDisplay(QWidget* parent=0);
        virtual ~BasicDisplay();

    signals:
        void sendMessage(QString const&);
        void logIntervalChange(QString const&);

    public slots:
        void onSendButtonClicked();
        void onProprietaryMessageReceived(QString const&);

        void onTime(QTime const&);
        void onDate(QDate const&);
        void onLatitude(double);
        void onLongitude(double);
        void onAltitude(double);
        void onFixQuality(int);
        void onFixStatus(QChar const&);
        void onFixMode(QChar const&);
        void onFixType(int);
        void onPdop(double);
        void onHdop(double);
        void onVdop(double);
        void onSatsInUse(int);
        void onGloSatsInView(int);
        void onGpsSatsInView(int);

        void onDirectionOfTravel(double);
        void onSpeedOfTravelKmPerHr(double);

        void siUnits();
        void usUnits();

    private: // functions
        void setDateTime();

    private: // data
        Ui::BasicDisplay* m_ui;
        QElapsedTimer* m_elapsedtime;
        QDateTime* m_datetime;
        double m_latitude;
        double m_longitude;
        double m_altitude;
        int m_glinview;
        int m_gpinview;
        int m_gnsinuse;
        int m_fixquality;
        int m_fixstatus;
        int m_fixmode;
        int m_fixtype;
        enum {SI_UNITS = 0, US_UNITS} m_units;
};

#endif //!defined BASICDISPLAY_H

