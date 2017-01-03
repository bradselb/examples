#include "RgbSliderWidget.h"
#include "ui_rgbSliders.h"

//#include <QtGui> 

RgbSliderWidget::RgbSliderWidget(QWidget* parent)
    :QWidget(parent),m_ui(new Ui::RgbSliders)
{
    m_ui->setupUi(this);
}


RgbSliderWidget::~RgbSliderWidget()
{
    delete m_ui;
}
