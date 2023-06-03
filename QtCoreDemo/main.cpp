#include <QtCore>
#include "numberlogic.h"
#include <iostream>
int main(int argc, char *argv[])
{
    NumberLogic numberLogic;
    std::cout << "Hello world" << std::endl;
    
    QCoreApplication app(argc, argv);
    QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer, SIGNAL(timeout()), &numberLogic, SLOT(onIncreace()));
    timer.start();
    app.exec();
}
