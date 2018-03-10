#include <QXmlDefaultHandler>

class QString;

class XmlHandler : public QXmlDefaultHandler
{
  public: 
    XmlHandler();
    ~XmlHandler();

    // content handler
    virtual bool characters(const QString& chars);
    virtual bool startDocument();
    virtual bool endDocument();

    virtual bool startElement(const QString& uri, const QString& localName, const QString& qName, const QXmlAttributes& atts);
    virtual bool endElement(const QString& uri, const QString& localName, const QString& qName);

    // error handler
    virtual bool error(QXmlParseException& ex);
    virtual QString errorString();
    virtual bool fatalError(QXmlParseException& ex);
    virtual bool warning(QXmlParseException& ex);

  private: // not implemented

  private: // data
    QString m_errorString;

    bool m_isElement;

};


