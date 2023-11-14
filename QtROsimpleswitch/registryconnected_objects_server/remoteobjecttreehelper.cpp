#include "remoteobjecttreehelper.h"
#include "remoteobjectstructs.h"

RemoteObjectTreeHelper::RemoteObjectTreeHelper(QObject*parent)
    : QObject(parent), m_rootObject(nullptr){
    setObjectName("RemoteObjectTreeHelper");
	m_listProperty << "abc" << "def";
}

void RemoteObjectTreeHelper::setRootObject(QObject* rootObject) {
    m_rootObject = rootObject;
	convertQObjectToRemoteStructList(m_rootObject, nullptr, m_objectsList);
}

bool RemoteObjectTreeHelper::enableObjectsRemoting() {
    return false;
}

QVariantList RemoteObjectTreeHelper::getObjects() {
	QVariantList list;
	foreach(RemoteObjectStruct objStruct, m_objectsList) {
		QVariantList temObj;
		temObj.append(objStruct.objName);
		temObj.append(objStruct.parentName);
		list.push_back(temObj);
	}
    return list;
}
QVariantList RemoteObjectTreeHelper::listProperty() {
	return m_listProperty;
}

void RemoteObjectTreeHelper::setListProperty(QVariantList list) {
	m_listProperty = list;
	Q_EMIT listPropertyChanged(m_listProperty);
}

QList<RemoteObjectStruct> RemoteObjectTreeHelper::getObjectsList() {
	qDebug() << " server QList<RemoteObjectStruct> RemoteObjectTreeHelper::getObjectsList()";
	return m_objectsList;
}

QMap<QString, QObject*> RemoteObjectTreeHelper::getRemoteObjects() {
	return m_objectMap;
}


void RemoteObjectTreeHelper::convertQObjectToRemoteStructList(QObject* itemObject, const QObject* parentObject, QList<RemoteObjectStruct>& objStructList) {
	if (!itemObject)
	{
		return;
	}
	RemoteObjectStruct remoteObjectStruct;
	if (convertQObjectToRemoteStruct(itemObject, parentObject, remoteObjectStruct))
	{
		objStructList.append(remoteObjectStruct);
	}

	QObjectList lists;
	QList<QByteArray> propNames = itemObject->dynamicPropertyNames();
	foreach(QByteArray propName, propNames)
	{
		const QVariant var = itemObject->property(propName);
		if (var.type() == QMetaType::QObjectStar && !var.isNull())
		{
			QObject* obj = var.value<QObject*>();
			lists << obj;
		}
	}

	for (int i = 0; i < lists.count(); ++i)
	{
		convertQObjectToRemoteStructList(lists.at(i), itemObject, objStructList);
	}
}
bool RemoteObjectTreeHelper::convertQObjectToRemoteStruct(QObject* itemObject, const QObject* parentObject, RemoteObjectStruct& remoteObjectStruct) {
	m_objectMap.insert(itemObject->objectName(), itemObject);

	const QString objectName = itemObject->objectName();
	QString parentName = "";
	if (itemObject->parent()) {
		parentName = itemObject->parent()->objectName();
	}
	remoteObjectStruct.objName = objectName;
	remoteObjectStruct.parentName = parentName;
	return true;
}
