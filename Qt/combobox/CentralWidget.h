#if !defined CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>

class QSerialPortInfo;

namespace Ui {class CentralWidget;}

class CentralWidget : public QWidget
{
    Q_OBJECT

    public:
        CentralWidget(QWidget* parent=0);
        ~CentralWidget();

    signals:
        void serialPortSelected(QSerialPortInfo const&);

    public slots:
        void onRefresh();
        void onComboBoxActivated(int idx);
        void onOk();

    private: // functions

    private: // data
        Ui::CentralWidget* m_ui;

        QList<QSerialPortInfo> m_ports;
        QSerialPortInfo m_selectedport;
};

#endif //!defined CENTRALWIDGET_H
