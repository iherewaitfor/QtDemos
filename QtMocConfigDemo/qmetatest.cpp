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
    qDebug() << ("class name is ") << object->metaObject()->className();
    
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
    int mCount = metaObject->methodCount();
    qDebug() << ("count of Methods is ") << mCount;
    for (int i = 0; i < mCount; i++) {
        QMetaMethod method = metaObject->method(i);
        QString methodName = method.name();
        QString methodSig = method.methodSignature();
        int retTypeId = method.returnType();
        QString retTypeName = QMetaType::typeName(retTypeId);
        QMetaMethod::MethodType methodType  = method.methodType();
        QStringList argTypes;
        QByteArrayList types = method.parameterTypes();
        for (int j = 0; j < types.length(); j++) {
            argTypes.push_back(types[j]);
        }
        method.parameterTypes();
        qDebug() << "methodName: " << methodName << " methodSig:" << methodSig << " retTypeId:" << retTypeId << " retTypeName:" << retTypeName << " methodType:" << methodType;
        qDebug() << "types: " << argTypes;
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
