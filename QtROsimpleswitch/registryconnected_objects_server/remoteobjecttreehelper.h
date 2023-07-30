#ifndef REMOTEOBJECTTREEHELPER_H
#define REMOTEOBJECTTREEHELPER_H

#include <QtCore>
#include "remoteobjectstructs.h"

class RemoteObjectTreeHelper : public QObject
{
    Q_OBJECT
public:
    RemoteObjectTreeHelper(QObject*parent = nullptr);

    void setRootObject(QObject* rootObject);
    bool enableObjectsRemoting();
    QList<RemoteObjectStruct> getObjects();
private:
    QObject* m_rootObject;
    QList<RemoteObjectStruct> m_objectsList;
};

#endif
