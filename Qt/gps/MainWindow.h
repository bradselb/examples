#if !defined MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();

    public slots:
        void setStatus(QString const&);

    private: // member functions
        void createToolBars();

    private: // widgets
        QToolBar* loggingToolBar;
        QAction* startAct;
        QAction* stopAct;

        QToolBar* unitsToolBar;
        QAction* siUnitsAct;
        QAction* usUnitsAct;
};


#endif //!defined MAINWINDOW_H

