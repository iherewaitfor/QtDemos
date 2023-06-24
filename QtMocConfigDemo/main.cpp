#include <QtCore>
#include "numberlogic.h"
#include <iostream>
#include "interfaceadapter.h"
#include "qmetatest.h"
#include "subnumberlogic.h"
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

    QVariantList argList2;
    argList2 << 10;
    argList2 << 20;
    interfaceAdapter.invokeMethod("testVoidAdd", argList2, "1234");

    QVariantList argList3;
    argList3 << 100;
    argList3 << 200;
    argList3 << "300";
    interfaceAdapter.invokeMethod("test3ArgAdd", argList3, "1235");
    SubNumberLogic subNumberLogic(&numberLogic);
    QMetaTest::getInstance()->getOBjectMetadata(&numberLogic);
    app.exec();
}
