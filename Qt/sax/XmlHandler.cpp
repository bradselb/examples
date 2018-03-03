#include "XmlHandler.h"

#include <QDebug>
#include <QString>
#include <QXmlAttributes>
#include <QXmlDefaultHandler>

XmlHandler::XmlHandler() : QXmlDefaultHandler(), m_isElement(false)
{
}

XmlHandler::~XmlHandler()
{
}

bool XmlHandler::characters(const QString& chars)
{
    bool isGood;
    isGood = true;
    if (m_isElement) qDebug() << chars;
    return isGood;
}

bool XmlHandler::startDocument()
{
    bool isGood;
    isGood = true;
    qDebug() << "startDocument()";
    return isGood;
}

bool XmlHandler::endDocument()
{
    bool isGood;
    isGood = true;
    qDebug() << "endDocument()";
    return isGood;
}

bool XmlHandler::startElement(const QString& uri, const QString& localName, const QString& qName, const QXmlAttributes& attribs)
{
    bool isGood;
    isGood = true;
    m_isElement = true;
    qDebug() << "startElement() " << "nsUri: " << uri << ", localName: " << localName << ", qName: " << qName;
    for (int i=0; i<attribs.count(); ++i) {
        qDebug() << attribs.localName(i) << "=" << attribs.value(i);
    }

    return isGood;
}

bool XmlHandler::endElement(const QString& uri, const QString& localName, const QString& qName)
{
    bool isGood;
    isGood = true;
    m_isElement = false;
    qDebug() << "endElement() " << "nsUri: " << uri << ", localName: " << localName << ", qName: " << qName;
    return isGood;
}

// error handler
bool XmlHandler::error(QXmlParseException& ex)
{
    bool isGood;
    isGood = true;
    qDebug() << "error() " << ex.message();
    return isGood;
}

QString XmlHandler::errorString()
{
    qDebug() << "errorString()";
    return QString("error message string");
}

bool XmlHandler::fatalError(QXmlParseException& ex)
{
    bool isGood;
    isGood = true;
    qDebug() << "fatalError() "  << ex.message();
    return isGood;
}

bool XmlHandler::warning(QXmlParseException& ex)
{
    bool isGood;
    isGood = true;
    qDebug() << "warning() "  << ex.message();
    return isGood;
}


