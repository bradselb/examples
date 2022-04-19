#if !defined BASICDISPLAY_H
#define BASICDISPLAY_H

#include <QWidget>
//#include <QString>
#include <QTime>

namespace Ui {class BasicDisplay;}


class BasicDisplay : public QWidget
{
    Q_OBJECT

    public:
        BasicDisplay(QWidget* parent=0);
        virtual ~BasicDisplay();

    public slots:
        void setTime(QTime const&);
        void setDate(QDate const&);
        void setDateTime(QDateTime const&);
        void setLatitude(double);
        void setLongitude(double);
        void setAltitude(double);
        void setFixQuality(int);
        void setFixStatus(QString const&);
        void setFixMode(QString const&);
        void setSatsInUse(int);
        void setGloSatsInView(int);
        void setGpsSatsInView(int);

    private: // functions

    private: // data
    Ui::BasicDisplay* m_ui;
    QTime m_elapsedtime;
    QDateTime* m_datetime;
    double m_latitude;
    double m_longitude;
    double m_altitude;
    int m_glinview;
    int m_gpinview;
    int m_fixquality;
};

#endif //!defined BASICDISPLAY_H
