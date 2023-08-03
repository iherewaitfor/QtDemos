#ifndef REMOTEOBJECTTREEHELPER_H
#define REMOTEOBJECTTREEHELPER_H

#include <QtCore>
#include "remoteobjectstructs.h"

class RemoteObjectTreeHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList listProperty READ listProperty WRITE setListProperty NOTIFY listPropertyChanged)
public:
    RemoteObjectTreeHelper(QObject*parent = nullptr);

    void setRootObject(QObject* rootObject);
    bool enableObjectsRemoting();
    Q_INVOKABLE QVariantList getObjects();
    Q_INVOKABLE QVariantList listProperty();
    Q_INVOKABLE void setListProperty(QVariantList list);
    Q_INVOKABLE QList<RemoteObjectStruct> getObjectsList();
    QMap<QString, QObject*> getRemoteObjects();
Q_SIGNALS:
    void listPropertyChanged(QVariantList);
private:
    void convertQObjectToRemoteStructList(QObject* itemObject, const QObject* parentObject, QList<RemoteObjectStruct>& objStructList);
    bool convertQObjectToRemoteStruct(QObject* itemObject, const QObject* parentObject, RemoteObjectStruct& remoteObjectStruct);

private:
    QObject* m_rootObject;
    QList<RemoteObjectStruct> m_objectsList;
    QMap<QString, QObject*> m_objectMap;
    QVariantList m_listProperty;
};

#endif
