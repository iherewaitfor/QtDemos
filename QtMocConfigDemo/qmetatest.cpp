#include "qmetatest.h"

QMetaTest::QMetaTest(QObject*parent)
    : QObject(parent){

}
QMetaTest* QMetaTest::getInstance() {
    static QMetaTest instance;
    return &instance;
}
void QMetaTest::test() {

}
void QMetaTest::getOBjectMetadata(QObject* object) {
    qDebug() << ("Object name is ") << object->objectName();
    
    const QMetaObject * metaObject = object->metaObject();
    int pCount = metaObject->propertyCount();
    qDebug() <<("count of properties is ") << pCount;
    for (int i = 0; i < metaObject->propertyCount(); i++)
    {
        QMetaProperty metaProperty = metaObject->property(i);
        QString propertyName = metaProperty.name();
        QString propertyType = metaProperty.typeName();
        int typeId = metaProperty.userType();
        qDebug() << "propertyName: " << propertyName << " propertyType:" << propertyType << " typeId:" << typeId;

    }
    QObjectList lists;
    QList<QByteArray> propNames = object->dynamicPropertyNames();
    int cCount = propNames.length();
    qDebug() << ("count of dynamicProperty is ") << cCount;
    for (int i = 0; i < propNames.length(); i++) {
        const QVariant var = object->property(propNames.at(i));
        if (var.type() == QMetaType::QObjectStar && !var.isNull())
        {
            QObject* obj = var.value<QObject*>();
            lists << obj;
            getOBjectMetadata(obj);
        }
    }




}
