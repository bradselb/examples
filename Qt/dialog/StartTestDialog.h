#if !defined STARTTESTDIALOG_H
#define STARTTESTDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QGroupBox;
class QLineEdit;
class QLabel;

class StartTestDialog : public QDialog
{
    Q_OBJECT

public:
    StartTestDialog();

private: // member functions
        
private: // data members
    QGroupBox* m_groupBox;
    QDialogButtonBox* m_buttonBox;
    QLabel* m_typeLabel;
    QLabel* m_lotNrLabel;
    QLabel* m_serialNrLabel;

    QLineEdit* m_typeLineEdit;
    QLineEdit* m_lotNrLineEdit;
    QLineEdit* m_serialNrLineEdit;

};

#endif //!defined STARTTESTDIALOG_H
