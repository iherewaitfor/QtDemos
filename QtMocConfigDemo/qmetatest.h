#ifndef QMETATEST_H
#define QMETATEST_H

#include <QObject>
#include <QtCore>

class QMetaTest : public QObject
{
    Q_OBJECT

public:
    QMetaTest(QObject*parent = nullptr);
public:
    static QMetaTest* getInstance();
    static void getOBjectMetadata(QObject*);
    static void test();

};

#endif
