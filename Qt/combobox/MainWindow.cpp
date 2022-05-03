#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "CentralWidget.h"

//MainWindow::MainWindow() : QMainWindow()
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    CentralWidget* centralwidget = new CentralWidget();
    this->setCentralWidget(centralwidget);
    this->statusBar()->showMessage("ready");
}

MainWindow::~MainWindow()
{
}

