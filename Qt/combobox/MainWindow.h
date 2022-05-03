#if !defined MainWindow_H
#define MainWindow_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget* parent=0);
        //MainWindow();
        virtual ~MainWindow();

    signals:

    public slots:

    private: // member functions

    private: // data
        Ui::MainWindow* m_ui;
};



#endif //!defined MainWindow_H
