#if !defined MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSerialPort;

class BasicDisplay;
class MessageDecoder;
class GpsReceiver;


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

    private:
        BasicDisplay* m_display;
        MessageDecoder* m_decoder;
        GpsReceiver* m_gps;

        QSerialPort* m_serialport;

};


#endif //!defined MAINWINDOW_H

