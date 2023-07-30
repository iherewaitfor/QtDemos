#include "remoteobjecttreehelper.h"

RemoteObjectTreeHelper::RemoteObjectTreeHelper(QObject*parent)
    : QObject(parent), m_rootObject(nullptr){
    setObjectName("RemoteObjectTreeHelper");
}

void RemoteObjectTreeHelper::setRootObject(QObject* rootObject) {
    m_rootObject = rootObject;
}

bool RemoteObjectTreeHelper::enableObjectsRemoting() {
    return false;
}

QList<RemoteObjectStruct> RemoteObjectTreeHelper::getObjects() {
    return m_objectsList;
}