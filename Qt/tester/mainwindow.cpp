#include <QtGui>

#include "mainwindow.h"
#include "centralwidget.h"

MainWindow::MainWindow()
{
    m_centralWidget = new CentralWidget();
    setCentralWidget(m_centralWidget);

    createActions();
    createMenus();
    //createToolBars();
    createStatusBar();
}


void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
//        loadFile(fileName);
    }
}


void MainWindow::save()
{
    return;
}


void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"), tr("The <b>Application</b> example demonstrates how to write modern GUI applications using Qt, with a menu bar, toolbars, and a status bar."));
}


void MainWindow::createActions()
{
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

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}


void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
//    m_fileMenu->addAction(newAct);
    m_fileMenu->addAction(openAct);
    m_fileMenu->addAction(saveAct);
    m_fileMenu->addAction(saveAsAct);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(exitAct);

    m_editMenu = menuBar()->addMenu(tr("&Edit"));
//    m_editMenu->addAction(cutAct);
//    m_editMenu->addAction(copyAct);
//    m_editMenu->addAction(pasteAct);

    menuBar()->addSeparator();

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(aboutAct);
//    m_helpMenu->addAction(aboutQtAct);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

