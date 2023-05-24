#include <QtWidgets>
#include "numberlogic.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(600, 240);
    window.setWindowTitle
          (QApplication::translate("childwidget", "Child widget"));
    window.show();
    NumberLogic numberLogic;
    QPushButton *button = new QPushButton(
        QApplication::translate("button increace", "button increace"), &window);
    button->move(100, 100);
    button->show();
    QMetaObject::Connection c = QObject::connect(button, SIGNAL(clicked()), &numberLogic, SLOT(onIncreace()),Qt::QueuedConnection);
    QLabel* lableShow = new QLabel(QApplication::translate("show counter", "show counter"), &window);
    lableShow->move(100,150);
    lableShow->show();
    QObject::connect(&numberLogic, SIGNAL(counterChangedText(QString)), lableShow, SLOT(setText(QString)), Qt::QueuedConnection);

    return app.exec();
}
