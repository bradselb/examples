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

    public slots:
        void onSendButtonClicked();
        void onProprietaryMessageReceived(QString const&);

        void setTime(QTime const&);
        void setDate(QDate const&);
        void setLatitude(double);
        void setLongitude(double);
        void setAltitude(double);
        void setFixQuality(int);
        void setFixStatus(QChar const&);
        void setFixMode(QChar const&);
        void setPdop(double);
        void setHdop(double);
        void setVdop(double);
        void setSatsInUse(int);
        void setGloSatsInView(int);
        void setGpsSatsInView(int);

        void setDirectionOfTravel(double);
        void setSpeedOfTravelKmPerHr(double);

    private: // functions
        void setDateTime();

    private: // data
        Ui::BasicDisplay* m_ui;
        QElapsedTimer* m_elapsedtime; // time to first fix
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
};

#endif //!defined BASICDISPLAY_H

