#ifndef INTERFACEADAPTER_H
#define INTERFACEADAPTER_H

#include <QObject>
#include <QMetaMethod>

class AutoSignalsEmitter;

class InterfaceAdapter : public QObject
{
    Q_OBJECT

public:
    explicit InterfaceAdapter(QObject* parent = nullptr);
    ~InterfaceAdapter();
    void initInterface(QObject* interfaceImpl, QString parentPath, QString interfaceName);
    QString interfacePath();
    void invokeMethod( const QString& method, const QVariantList& args, const QString& callbackId);

    void transerProxySignal(QString signalName, QVariantList arguments);

private slots:
    void onProxySignal(QObject* sender, QMetaMethod signal, QVariantList args);

private:
    void parseSignal();
    void parseAndInjectApi();

private:
    QString m_interfaceName;
    QString m_parentPath;

    QObject* m_interfaceObject;

    QList<AutoSignalsEmitter*> m_autoSignalsEmitters;
};

#endif
