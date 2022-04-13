#if !defined MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include <QMainWindow>

class CentralWidget;
class QAction;
class QMenu;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void open();
    void save();
    void saveAs();
    void about();

private: // member functions
    void createActions();
    void createMenus();
    void createStatusBar();


private: // data
    CentralWidget* m_centralWidget;
    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_helpMenu;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* exitAct;
    QAction* aboutAct;
};


#endif //!defined MYMAINWINDOW_H

