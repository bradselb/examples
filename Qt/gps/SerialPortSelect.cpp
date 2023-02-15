#include "SerialPortSelect.h"
#include "ui_SerialPortSelect.h"

#include <QDialog>
#include <QWidget>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QString>
#include <QList>

#include <string.h> // memset(), snprintf()

//----------------------------------------------------------------------------
SerialPortSelect::SerialPortSelect(QWidget* parent)
  : QDialog(parent)
  , m_ports()
  , m_selectedport()
{
    m_ui = new Ui::SerialPortSelect;
    m_ui->setupUi(this);

    m_ui->label_00->setText("port name"); m_ui->label_01->setText("");
    m_ui->label_10->setText("system location"); m_ui->label_11->setText("");
    m_ui->label_20->setText("manufacturer"); m_ui->label_21->setText("");
    m_ui->label_30->setText("description"); m_ui->label_31->setText("");
    m_ui->label_40->setText("serial number"); m_ui->label_41->setText("");
    m_ui->label_50->setText("vender id"); m_ui->label_51->setText("");
    m_ui->label_60->setText("product id"); m_ui->label_61->setText("");

    connect(m_ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshButtonClicked()));
    connect(m_ui->okButton, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
    connect(m_ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    connect(m_ui->comboBox, SIGNAL(activated(int)), this, SLOT(onComboBoxActivated(int)));

    this->onRefreshButtonClicked();
}

//----------------------------------------------------------------------------
SerialPortSelect::~SerialPortSelect()
{
    delete m_ui;
}


//----------------------------------------------------------------------------
// (re)populate the combo box
void SerialPortSelect::onRefreshButtonClicked()
{
    m_ui->comboBox->clear();
    m_ports.clear();

    m_ports = QSerialPortInfo::availablePorts();

    QList<QSerialPortInfo>::const_iterator iter;
    iter = m_ports.begin();
    while (iter != m_ports.end()) {
        m_ui->comboBox->addItem(iter->portName());
        ++iter;
    }

    if (m_ui->comboBox->count()>0) onComboBoxActivated(0);
}

//----------------------------------------------------------------------------
void SerialPortSelect::onOkButtonClicked()
{
    emit serialPortSelected(m_selectedport);
    this->close();
}

//----------------------------------------------------------------------------
void SerialPortSelect::onCancelButtonClicked()
{
    this->close();
}

//----------------------------------------------------------------------------
void SerialPortSelect::onComboBoxActivated(int idx)
{
    m_selectedport = m_ports.at(idx);

    m_ui->label_01->setText(m_selectedport.portName());
    m_ui->label_11->setText(m_selectedport.systemLocation());
    m_ui->label_21->setText(m_selectedport.manufacturer());
    m_ui->label_31->setText(m_selectedport.description());
    m_ui->label_41->setText(m_selectedport.serialNumber());

    // g++ chokes on these. It warns about ambiguous conversion and chooses the wrong conversion.
    //m_ui->label_51->setText(QString("%1").arg(m_selectedport.vendorIdentifier(), 0, (int)16, '0'));
    //m_ui->label_61->setText(QString("%1").arg(m_selectedport.productIdentifier(), 0, 16, '0'));

    char buf[8];
    if (m_selectedport.hasVendorIdentifier()) {
        memset(buf, 0, sizeof buf);
        snprintf(buf, sizeof buf, "%#1.4x", m_selectedport.vendorIdentifier());
        m_ui->label_51->setText(QString(buf));
    } else {
        m_ui->label_51->setText("");
    }

    if (m_selectedport.hasProductIdentifier()) {
        memset(buf, 0, sizeof buf);
        snprintf(buf, sizeof buf, "%#1.4x", m_selectedport.productIdentifier());
        m_ui->label_61->setText(QString(buf));
    } else {
        m_ui->label_61->setText("");
    }
}

