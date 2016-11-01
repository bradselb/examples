#if !defined MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include <QMainWindow>


class QAction;
class QMenu;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void open();
    void save();
    void saveAs();
    void about();

private: // member functions
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    void loadFile(QString const& fileName);
    bool saveFile(QString const& fileName);
    void setCurrentFile(QString const& fileName);
    QString strippedName(QString const& fullFileName);


private: // data
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* exitAct;
    QAction* aboutAct;


};


#endif //!defined MYMAINWINDOW_H

