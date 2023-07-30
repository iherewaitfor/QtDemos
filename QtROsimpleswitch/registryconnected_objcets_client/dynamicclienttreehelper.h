#ifndef _DYNAMICCLIENTTREEHELPER_H
#define _DYNAMICCLIENTTREEHELPER_H

#include <QObject>
#include <QSharedPointer>

#include <QRemoteObjectNode>
#include <qremoteobjectdynamicreplica.h>
#include<QRemoteObjectPendingCallWatcher>
#include <QTimer>;

class DynamicClientTreeHelper : public QObject
{
    Q_OBJECT
public:
    DynamicClientTreeHelper(QSharedPointer<QRemoteObjectDynamicReplica> ptr);
    ~DynamicClientTreeHelper() override;
public Q_SLOTS:
    void initConnection_slot(); //QRemoteObjectDynamicReplica
    void stateChanged_slot(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState);
    void pendingCallResult(QRemoteObjectPendingCallWatcher* self);
private:
    QSharedPointer<QRemoteObjectDynamicReplica> reptr;// holds reference to replica
    bool m_binitConnection;
    QMap<QString, QSharedPointer<QRemoteObjectDynamicReplica>> objectsMap;
 };

#endif

