#ifndef NUMBERLOGIC_H
#define NUMBERLOGIC_H

#include <QWidget>

class NumberLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 counter READ counter WRITE setCounter)

public:
    NumberLogic(QObject*parent = nullptr);
    qint32 counter();
    void setCounter(qint32 counter);
public slots:
    void onIncreace();
signals:
    void counterChanged(int counter);
    void counterChangedText(QString strCounter);
private:
    qint32 m_counter;
};

#endif
