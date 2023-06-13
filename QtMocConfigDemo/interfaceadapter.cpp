#include "interfaceadapter.h"
#include "autosignalsemitter.h"

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