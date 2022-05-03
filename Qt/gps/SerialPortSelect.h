#if !defined SERIALPORTSELECT_H
#define SERIALPORTSELECT_H

#include <QDialog>
#include <QWidget>
#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>


namespace Ui {class SerialPortSelect;}

class SerialPortSelect : public QDialog
{
    Q_OBJECT

    public:
        SerialPortSelect(QWidget* parent=0);
        ~SerialPortSelect();

    signals:
        void serialPortSelected(QSerialPortInfo const&);

    public slots:
        void onRefreshButtonClicked();
        void onOkButtonClicked();
        void onCancelButtonClicked();
        void onComboBoxActivated(int idx);

    private:
        Ui::SerialPortSelect* m_ui;

        QList<QSerialPortInfo> m_ports;
        QSerialPortInfo m_selectedport;
};

#endif //!defined SERIALPORTSELECT_H

