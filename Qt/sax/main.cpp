#include <QtCore>
#include <QXmlSimpleReader>

#include "XmlHandler.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QXmlSimpleReader myXmlReader;
    XmlHandler myXmlHandler;

    myXmlReader.setContentHandler(&myXmlHandler);
    myXmlReader.setErrorHandler(&myXmlHandler);

    QStringList args(app.arguments());
    QStringList::const_iterator iter;
    for (iter=args.begin(); iter!=args.end(); ++iter) {
        QString filename(*iter);
        QFile xmlfile(filename);
        if (xmlfile.exists() && xmlfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            myXmlReader.parse(&xmlfile);
            xmlfile.close();
        }
    }

//    return app.exec();
    return 0;
}
