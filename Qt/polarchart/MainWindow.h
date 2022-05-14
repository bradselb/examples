#if !defined BKS_MAINWINDOW_H
#define BKS_MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {class MainWindow;}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget* parent=0);
        ~MainWindow();

    public slots:
        void setStatus(QString const&);

    private:
        Ui::MainWindow* m_ui;

};

#endif //!defined MAINWINDOW_H

