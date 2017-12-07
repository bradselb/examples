#if !defined RGB_SLIDER_WIDGET_H
#define RGB_SLIDER_WIDGET_H

#include <QWidget>

// fwd decls
namespace Ui { class RgbSliders; }



class RgbSliderWidget : public QWidget
{
    Q_OBJECT

public: 
    RgbSliderWidget(QWidget* parent=0);
    virtual ~RgbSliderWidget();

private:
    Ui::RgbSliders* m_ui;

};

#endif // !defined RGB_SLIDER_WIDGET_H

