
#include "centralwidget.h"
#include <QtGui>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

CentralWidget::CentralWidget()
{
    // DUT info
    m_dutTypeLabel = new QLabel(tr("DUT Type:"));
    m_lotNrLabel = new QLabel(tr("Lot Number:"));
    m_serialNrLabel = new QLabel(tr("Serial Number:"));

    m_dutTypeLineEdit = new QLineEdit();
    m_lotNrLineEdit = new QLineEdit();
    m_serialNrLineEdit = new QLineEdit();

    m_dutTypeLineEdit->setReadOnly(true);
    m_dutTypeLineEdit->setText("Type A");
 
    QFormLayout* dutInfoLayout = new QFormLayout();
    dutInfoLayout->addRow(m_dutTypeLabel, m_dutTypeLineEdit);
    dutInfoLayout->addRow(m_lotNrLabel, m_lotNrLineEdit);
    dutInfoLayout->addRow(m_serialNrLabel, m_serialNrLineEdit);

    m_dutInfoGroupBox = new QGroupBox(tr("DUT Information"));
    m_dutInfoGroupBox->setLayout(dutInfoLayout);

    // test Results
    m_firstResultLabel = new QLabel(tr("first result:"));
    m_secondResultLabel = new QLabel(tr("second result"));
    m_thirdResultLabel = new QLabel(tr("third result"));
    m_firstResultLineEdit = new QLineEdit();
    m_secondResultLineEdit = new QLineEdit();
    m_thirdResultLineEdit = new QLineEdit();

    QFormLayout* testResultsLayout = new QFormLayout();
    testResultsLayout->addRow(m_firstResultLabel, m_firstResultLineEdit);
    testResultsLayout->addRow(m_secondResultLabel, m_secondResultLineEdit);
    testResultsLayout->addRow(m_thirdResultLabel, m_thirdResultLineEdit);

    m_testResultsGroupBox = new QGroupBox(tr("Test Results"));
    m_testResultsGroupBox->setLayout(testResultsLayout);

    // push buttons
    m_startButton = new QPushButton("&Start", this);
    m_cancelButton = new QPushButton("Cancel", this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_startButton);
    buttonLayout->addWidget(m_cancelButton);

    m_buttonGroupBox = new QGroupBox(tr("Test Results"));
    m_buttonGroupBox->setLayout(buttonLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_dutInfoGroupBox);
    mainLayout->addWidget(m_testResultsGroupBox);
    mainLayout->addWidget(m_buttonGroupBox);

    this->setLayout(mainLayout);

    setWindowTitle("Central Widget");


    connect(m_startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(abort()));

}


// slots...
void CentralWidget::start()
{
    emit this->startTest();
}


void CentralWidget::abort()
{
    emit this->abortTest();
}

