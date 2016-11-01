#if !defined MY_CENTRAL_WIDGET_H
#define MY_CENTRAL_WIDGET_H

#include <QWidget>

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;


class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget();


public signals:
    void startTest();
    void abortTest();


private slots:
    void start();
    void cancel();


private: // member functions

private: // data members
    QGroupBox* m_dutInfoGroupBox;
    QLabel* m_dutTypeLabel;
    QLabel* m_lotNrLabel;
    QLabel* m_serialNrLabel;
    QLineEdit* m_dutTypeLineEdit;
    QLineEdit* m_lotNrLineEdit;
    QLineEdit* m_serialNrLineEdit;

    QGroupBox* m_testResultsGroupBox;
    QLabel* m_firstResultLabel;
    QLabel* m_secondResultLabel;
    QLabel* m_thirdResultLabel;
    QLineEdit* m_firstResultLineEdit;
    QLineEdit* m_secondResultLineEdit;
    QLineEdit* m_thirdResultLineEdit;
//    QLabel* m_firstPassFailIndicatorLabel;
//    QLabel* m_secondPassFailIndicatorLabel;
//    QLabel* m_thirdPassFailIndicatorLabel;


//    QGroupBox* m_buttonGroupBox;
    QPushButton* m_startButton;
    QPushButton* m_cancelButton


};

#endif // !defined MY_CENTRAL_WIDGET_H

