#include <QtCore>
#include <QCoreApplication>

int main(int argc, char** argv)
{
    int rc;
    QCoreApplication app(argc, argv);
    QStringList args(app.arguments());

    QStringList::const_iterator iter;
    for (iter=args.begin(); iter!=args.end(); ++iter) {
        printf("%s\n", iter->toAscii().data());
    }

    rc = app.exec();
    return rc;
}
