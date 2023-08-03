#ifndef REMOTEOBJECTSTRUCTS_H
#define REMOTEOBJECTSTRUCTS_H

#include <QtCore>

struct RemoteObjectStruct
{
    QString objName;
    QString parentName;
    friend QDataStream& operator << (QDataStream& dataStream, const RemoteObjectStruct& object)
    {
        dataStream << object.objName;
        dataStream << object.parentName;
        return dataStream;
    }

    friend QDataStream& operator >> (QDataStream& dataStream, RemoteObjectStruct& object)
    {
        dataStream >> object.objName;
        dataStream >> object.parentName;
        return dataStream;
    }
    RemoteObjectStruct() = default;
    ~RemoteObjectStruct() = default;
    RemoteObjectStruct(const QString& objectName, const QString& parentName) {
        this->objName = objectName;
        this->parentName = parentName;
    }
    RemoteObjectStruct(const RemoteObjectStruct& objStruct) {
        objName = objStruct.objName;
        parentName = objStruct.parentName;
    }
    RemoteObjectStruct& operator = (const RemoteObjectStruct& objStruct) {
        if (this == &objStruct) {
            return *this;
        }
        RemoteObjectStruct obj;
        obj.objName = objStruct.objName;
        obj.parentName = objStruct.parentName;
        return obj;
    }
};

//QDataStream& operator << (QDataStream& dataStream, const QList<RemoteObjectStruct>& list)
//{
//    dataStream << list.size();
//    foreach(const RemoteObjectStruct & objStruct, list) {
//        dataStream << objStruct;
//    }
//    return dataStream;
//}
//
//QDataStream& operator >> (QDataStream& dataStream, QList<RemoteObjectStruct>& list)
//{
//    int size = 0;
//    dataStream >> size;
//    for (int i = 0; i < size; i++) {
//        RemoteObjectStruct objStruct;
//        dataStream >> objStruct;
//        list.append(objStruct);
//    }
//    return dataStream;
//}


Q_DECLARE_METATYPE(RemoteObjectStruct);
Q_DECLARE_METATYPE(QList<RemoteObjectStruct>);
#endif
