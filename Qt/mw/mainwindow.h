#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool doYouReallyWantToDoThis();
    void loadFile(QString const& fileName);
    bool saveFile(QString const& fileName);
    void setCurrentFile(QString const& fileName);
    QString strippedName(QString const& fullFileName);

    QPlainTextEdit* textEdit;
    QString curFile;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* exitAct;
    QAction* cutAct;
    QAction* copyAct;
    QAction* pasteAct;
    QAction* aboutAct;
    QAction* aboutQtAct;
};



