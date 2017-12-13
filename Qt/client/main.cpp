#include <QtCore>

#include "Client.h"

int main(int argc, char** argv)
{
    int rc = -1;
    QCoreApplication app(argc, argv);

    Client* client = new Client(&app);
    QObject::connect(client, SIGNAL(bailout()), &app, SLOT(quit()));

    // get host name from command line args and, optionally, the port number too.
    QString host;
    QString port("1735");
    QStringList args(app.arguments());
    QStringList::const_iterator iter;
    for (iter=args.begin(); iter!=args.end(); ++iter) {
        QString hostCmdLineSw("--host");
        QString portCmdLineSw("--port");
        if (iter->startsWith(hostCmdLineSw)) {
            //  --host=example.domain.com
            host = iter->split("=").at(1);
        } else if (iter->startsWith(portCmdLineSw)) {
            //  --port=1735
            port = iter->split("=").at(1);
        }
        //printf("%s\n", iter->toAscii().data());
    }

    if (host.isEmpty()) {
        // print a helpful usage message and exit with an error code.
        rc = -1;
    } else {
        // display an informative success message and start the event loop.
        client->connectToHost(host, port.toInt());
        rc = app.exec();
    }

    return rc;
}
