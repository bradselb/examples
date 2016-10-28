
#include <QApplication>
#include "StartTestDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StartTestDialog dialog;
    dialog.show();

    return app.exec();
}



