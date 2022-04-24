#include <qdir.h>
#include <qfile.h>
#include <qstring.h>
#include <qbytearray.h>

#include <QIODevice>
#include <QDomElement>
#include <QDomDocument>

int main(int argc, char* argv[])
{
    QString filename("config.xml");
    QFile f(filename);
    QDomDocument doc;

    doc.setContent(dynamic_cast<QIODevice*>(&f), false);

    QDomNodeList nodes = doc.elementsByTagName(QString("pythonpath"));
    for (int i = 0; i < nodes.length(); ++i) {
        QString s;
        s = nodes.at(i).toElement().text();
        s.replace(QString("$PYTHONHOME"), QString("/usr/bin/python27"));
        s.replace(QString("$PROJECT_PATH"), QString("~/mysample"));
        s.replace(QString("$PYTHON_VERSION"), QString("27"));

        printf("%s\n", s.toStdString().c_str());
    }
    return 0;
}

