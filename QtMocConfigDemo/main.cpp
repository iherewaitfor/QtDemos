#include <QtCore>
#include "numberlogic.h"
#include <iostream>
#include "interfaceadapter.h"
int main(int argc, char *argv[])
{
    NumberLogic numberLogic;
    std::cout << "Hello world" << std::endl;
    
    QCoreApplication app(argc, argv);
    QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer, SIGNAL(timeout()), &numberLogic, SLOT(onIncreace()));
    timer.start();

    InterfaceAdapter interfaceAdapter;
    interfaceAdapter.initInterface(&numberLogic, "", "numberlogic");
    QVariantList argList;
    argList << 10;
    interfaceAdapter.invokeMethod("addCount", argList, "123");

    app.exec();
}
