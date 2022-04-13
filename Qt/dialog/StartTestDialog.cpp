#include "StartTestDialog.h"

#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>

StartTestDialog::StartTestDialog()
{

    m_typeLabel = new QLabel(tr("Type:"));
    m_lotNrLabel = new QLabel(tr("Lot Number:"));
    m_serialNrLabel = new QLabel(tr("Serial Number:"));

    m_typeLineEdit = new QLineEdit();
    m_lotNrLineEdit = new QLineEdit();
    m_serialNrLineEdit = new QLineEdit();
    
    QFormLayout* formlayout = new QFormLayout();
    formlayout->addRow(m_typeLabel, m_typeLineEdit);
    formlayout->addRow(m_lotNrLabel, m_lotNrLineEdit);
    formlayout->addRow(m_serialNrLabel, m_serialNrLineEdit);

    m_groupBox = new QGroupBox(tr("DUT Information"));
    m_groupBox->setLayout(formlayout);

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_groupBox);
    mainLayout->addWidget(m_buttonBox);

    this->setLayout(mainLayout);

    setWindowTitle("Start Test");

    return;
}


