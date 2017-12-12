#include <QtCore>

#include "Client.h"

int main(int argc, char** argv)
{
    int rc;
    QCoreApplication app(argc, argv);

    Client* client = new Client(&app);
    QObject::connect(client, SIGNAL(bailout()), &app, SLOT(quit()));

    QStringList args(app.arguments());
    QStringList::const_iterator iter;
    for (iter=args.begin(); iter!=args.end(); ++iter) {
        printf("%s\n", iter->toAscii().data());
    }

    // TODO: get these from commmand line switches. 
    client->connectToHost(QString("harpina"), 1735);

    rc = app.exec();
    return rc;
}
