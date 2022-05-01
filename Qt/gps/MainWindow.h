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

    private: // objects
        BasicDisplay* m_display;
        MessageDecoder* m_decoder;
        GpsReceiver* m_gps;
        QSerialPort* m_serialport;

    private slots:
        void newFile();
        void setFile();
        void startLogging();
        void stopLogging();
        void changeDisplayedUnits();

    private: // member functions
        void createActions();
        void createMenus();
        void createToolBar();

    private: // widgets
        QToolBar* toolBar;
        QAction* startAct;
        QAction* stopAct;
        QAction* changeAct;

        QMenu* fileMenu;
        QAction* newAct; // create a new, empty logfile
        QAction* setAct; // specify an existing logfile

        QMenu* deviceMenu;
        QAction* openAct;
        QAction* closeAct;

};


#endif //!defined MAINWINDOW_H

