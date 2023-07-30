#ifndef REMOTEOBJECTSTRUCTS_H
#define REMOTEOBJECTSTRUCTS_H

#include <QtCore>

typedef struct RemoteObjectStruct
{
    QString objName;
    QString parentName;
}RemoteObjectStruct;
Q_DECLARE_METATYPE(RemoteObjectStruct);
#endif
