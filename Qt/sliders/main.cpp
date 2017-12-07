
#include <QApplication>
#include <QMainWindow>
#include "RgbSliderWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainwindow;

    mainwindow.setCentralWidget(new RgbSliderWidget(&mainwindow));

    mainwindow.show();

    return app.exec();
}

