#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMainWindow>
#include <QWidget>
#include <QChartView>
#include <QPolarChart>
#include <QScatterSeries>
#include <QValueAxis>

using namespace QtCharts;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QValueAxis* azimuthAxis = new QValueAxis();
    azimuthAxis->setRange(0.0, 360.0);
    azimuthAxis->setTickCount(13);
    //azimuthAxis->setTickInterval(30.0);
    azimuthAxis->setVisible();

    QValueAxis* elevationAxis = new QValueAxis();
    elevationAxis->setRange(0.0 ,90.0);
    elevationAxis->setTickCount(10);
    elevationAxis->setVisible();
    elevationAxis->setLabelsVisible(false);


    QScatterSeries* dataSeries = new QScatterSeries();
    //             (azimuth, elevation)
    dataSeries->append(135.0, 90-27.0);
    dataSeries->append( 45.0, 90-22.0);
    dataSeries->append( 63.0, 90-17.0);
    dataSeries->append(330.0, 90-77.0);
    dataSeries->append(243.0, 90-37.0);
    dataSeries->append(197.0, 90- 7.0);


    QPolarChart* chart = new QPolarChart();
    chart->legend()->hide();
    chart->addSeries(dataSeries);
    chart->addAxis(elevationAxis, QPolarChart::PolarOrientationRadial);
    chart->addAxis(azimuthAxis, QPolarChart::PolarOrientationAngular);
    dataSeries->attachAxis(azimuthAxis);
    dataSeries->attachAxis(elevationAxis);

    QChartView *chartView = new QChartView(chart);

    this->setCentralWidget(chartView);
    this->resize(1024,768);
    this->show();

    statusBar()->showMessage("Ready");
};


// ---------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

// ---------------------------------------------------------------------------
void MainWindow::setStatus(QString const& message)
{
    statusBar()->showMessage(message);
}

