
#include <QApplication>

#include "restinspector.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RestInspector restInspector;
    restInspector.show();
    return app.exec();
}
