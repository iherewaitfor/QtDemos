#include "interfaceadapter.h"
#include "autosignalsemitter.h"
#include <iostream>
#include "metainvoker.h"
InterfaceAdapter::InterfaceAdapter(QObject*parent)
    : QObject(parent){

}

InterfaceAdapter::~InterfaceAdapter()
{

}
void InterfaceAdapter::initInterface(QObject* interfaceImpl, QString parentPath, QString interfaceName) {
    m_interfaceObject = interfaceImpl;
    m_interfaceName = interfaceName;
    m_parentPath = parentPath;

    parseSignal();

    parseAndInjectApi();
}
QString InterfaceAdapter::interfacePath()
{
    if (m_parentPath.isEmpty())
    {
        return m_interfaceName;
    }
    else
    {
        return m_parentPath + "." + m_interfaceName;
    }
}

void InterfaceAdapter::invokeMethod(const QString& method, const QVariantList& args, const QString& callbackId) {

    const QMetaObject* metaObject = m_interfaceObject->metaObject();
    QObject* sourceObject = m_interfaceObject;

    for (int i = 0; i != metaObject->methodCount(); ++i)
    {
        QMetaMethod metaMethod = metaObject->method(i);
        if (metaMethod.methodType() == QMetaMethod::Method
            || metaMethod.methodType() == QMetaMethod::Slot)
        {
            QString methodName = QLatin1String(metaMethod.methodSignature());
            methodName = methodName.left(methodName.indexOf("("));

            if (methodName == method)
            {
                //auto paramTypes = metaMethod.parameterTypes();
                //auto returnTypeID = metaMethod.returnType();
                ////QVariant retVale;
                //void* retVal = QMetaType::create(returnTypeID);
                //int num = 10;
                //QVariantList args2 = args;
                //bool bInvokeOK = false;
                //
                //// to do QVariant to void *
                //if (paramTypes.size() == 1) {
                //    //bInvokeOK = metaMethod.invoke(sourceObject, QGenericReturnArgument("int", retVale),
                //    //    QGenericArgument("int", &num));
                //    bInvokeOK = metaMethod.invoke(sourceObject, QGenericReturnArgument(QMetaType::typeName(returnTypeID), retVal),
                //        QGenericArgument(paramTypes.at(0).constData(), const_cast<void*>(args.at(0).constData())));
                //}
                //QVariant retVariant(returnTypeID, retVal);
                //std::cout << "bInvokeOK: " << bInvokeOK << " returnvalue is " << retVariant.toInt() << std::endl;
                
                MetaInvoker metaInvoker;
                metaInvoker.object = m_interfaceObject;
                metaInvoker.args = args;
                metaInvoker.metaMethod = metaMethod;
                metaInvoker.run();

                std::cout << "bInvokeOK: " << metaInvoker.ok << " returnvalue is " << metaInvoker.result.toString().toStdString() << std::endl;
                
                break;
            }
        }
    }
}

void InterfaceAdapter::onProxySignal(QObject* sender, QMetaMethod signal, QVariantList args)
{
    (void)sender;

    QString methodName = QLatin1String(signal.methodSignature());

    methodName = methodName.left(methodName.indexOf("("));

    transerProxySignal(methodName, args);
}
void InterfaceAdapter::transerProxySignal(QString eventName, QVariantList arguments)
{
    //to do: transerProxySignal
    std::cout << " transerProxySignal: " << eventName.toStdString() << " arguments size " << arguments.size() << std::endl;
    if (arguments.size() > 0) {
        std::cout << " fist arg value is: " << arguments.at(0).toString().toStdString() << std::endl;
    }

}

void InterfaceAdapter::parseSignal()
{
    const QMetaObject* metaObject = m_interfaceObject->metaObject();

    for (int i = 0; i != metaObject->methodCount(); ++i)
    {
        QMetaMethod method = metaObject->method(i);
        if (method.methodType() == QMetaMethod::Signal)
        {
            QString signature = QLatin1String(method.methodSignature());
            QString eventName = signature.left(signature.indexOf("("));
            if (eventName == "destroyed")
            {
                continue;
            }

            signature.prepend("2");

            AutoSignalsEmitter* signalEmitter = new AutoSignalsEmitter(method, this);
            connect(m_interfaceObject, qFlagLocation(signature.toUtf8().constData()), signalEmitter, SLOT(proxySlot()));
            connect(signalEmitter, SIGNAL(proxySignal(QObject*, QMetaMethod, QVariantList)), SLOT(onProxySignal(QObject*, QMetaMethod, QVariantList)));

            m_autoSignalsEmitters.append(signalEmitter);
        }
    }
}
void InterfaceAdapter::parseAndInjectApi()
{
 
}