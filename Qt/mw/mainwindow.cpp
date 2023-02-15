#include <mainwindow.h>

#include <QtGui>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>


MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
}


void MainWindow::closeEvent(QCloseEvent* event)
{
    if (doYouReallyWantToDoThis()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


void MainWindow::newFile()
{
    if (doYouReallyWantToDoThis()) {
        textEdit->clear();
        setCurrentFile("");
    }
}


void MainWindow::open()
{
    if (doYouReallyWantToDoThis()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}


bool MainWindow::save()
{
    bool file_saved;

    if (curFile.isEmpty()) {
        file_saved = saveAs();
    } else {
        file_saved = saveFile(curFile);
    }

    return file_saved;
}


bool MainWindow::saveAs()
{
    bool file_saved = false;

    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty()) {
        file_saved = saveFile(fileName);
    }

    return file_saved;
}


void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"), tr("The <b>Application</b> example demonstrates how to write modern GUI applications using Qt, with a menu bar, toolbars, and a status bar."));
}


void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}


void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));

}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


void MainWindow::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}


void MainWindow::writeSettings()
{
    QSettings settings("Trolltech", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


bool MainWindow::doYouReallyWantToDoThis()
{
    bool yes_please = true;
    bool file_saved = false;

    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;

        ret = QMessageBox::warning(this, tr("Application"), tr("The document has been modified.\nDo you want to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            file_saved = save();
        } else if (ret == QMessageBox::Cancel) {
            yes_please = false;
        }
    }
    return yes_please || file_saved;
}


void MainWindow::loadFile(QString const& fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
    } else {

        QTextStream in(&file);
        textEdit->setPlainText(in.readAll());

        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File loaded"), 2000);
    }
}



bool MainWindow::saveFile(QString const& fileName)
{
    bool file_saved;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
        file_saved = false;

    } else {

        QTextStream out(&file);
        out << textEdit->toPlainText();

        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File saved"), 2000);

        file_saved = true;
    }

    return file_saved;
}


void MainWindow::setCurrentFile(QString const& fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}


QString MainWindow::strippedName(QString const& fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


