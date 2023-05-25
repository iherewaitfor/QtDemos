#include "numberlogic.h"

NumberLogic::NumberLogic(QObject*parent)
    : QObject(parent),m_counter(0){

}
qint32 NumberLogic::counter() {
    return m_counter;
}
void NumberLogic::setCounter(qint32 counter) {
    this->m_counter = counter;
}
void NumberLogic::addCount(qint32 i) {
    m_counter += i;
}
void NumberLogic::nornmalAddCount(qint32 i) {
    m_counter += i;
}

void NumberLogic::onIncreace() {
    m_counter++;
    emit counterChanged(m_counter);
    emit counterChangedText(QString::number(m_counter));
}