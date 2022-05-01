#if !defined MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSerialPort;
class QAction;
class QMenu;


class BasicDisplay;
class MessageDecoder;
class GpsReceiver;


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

    public slots:
        void setStatus(QString const&);

    private: // member functions
        void createToolBars();

    private: // objects
        BasicDisplay* m_display;
        MessageDecoder* m_decoder;
        GpsReceiver* m_gps;
        QSerialPort* m_serialport;

    private: // widgets
        QToolBar* loggingToolBar;
        QAction* startAct;
        QAction* stopAct;

        QToolBar* unitsToolBar;
        QAction* siUnitsAct;
        QAction* usUnitsAct;
};


#endif //!defined MAINWINDOW_H

