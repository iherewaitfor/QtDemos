#ifndef NUMBERLOGIC_H
#define NUMBERLOGIC_H

#include <QtCore>

class NumberLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 counter READ counter WRITE setCounter NOTIFY counterChanged)

public:
    NumberLogic(QObject*parent = nullptr);
    Q_INVOKABLE qint32 counter();
    Q_INVOKABLE void setCounter(qint32 counter);
    Q_INVOKABLE int addCount(qint32 i); // can be invoked via the meta-object system
    void nornmalAddCount(qint32 i);
    Q_INVOKABLE QString addQString(QString strN);
    Q_INVOKABLE void addNoReturn(qint32 i);
public slots:
    void onIncreace();
    QString addQStringSlot(QString strN);
signals:
    void counterChanged(int counter);
    void counterChangedText(QString strCounter);
private:
    qint32 m_counter;
};

#endif
