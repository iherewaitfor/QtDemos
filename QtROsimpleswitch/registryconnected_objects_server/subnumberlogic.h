#ifndef SUBNUMBERLOGIC_H
#define SUBNUMBERLOGIC_H

#include <QObject>

class SubNumberLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 counter READ counter WRITE setCounter)

public:
    SubNumberLogic(QObject*parent = nullptr);
    qint32 counter();
    void setCounter(qint32 counter);
    Q_INVOKABLE int addCount(qint32 i); // can be invoked via the meta-object system
    void nornmalAddCount(qint32 i);
    Q_INVOKABLE void testVoidAdd(qint32 a, qint32 b);
    Q_INVOKABLE int test3ArgAdd(qint32 a, qint32 b, QString c);
    Q_INVOKABLE int test4ArgAdd(qint32 a, qint32 b, QString c, QString d);
public slots:
    void onIncreace();
signals:
    void counterChanged(int counter);
    void counterChangedText(QString strCounter);
private:
    qint32 m_counter;
};

#endif
