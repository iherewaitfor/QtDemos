#ifndef METAINVOKER_H
#define METAINVOKER_H

#include <QtCore>

struct MetaInvoker
{
    bool ok = false;
    QObject* object;
    QMetaMethod metaMethod;
    QVariantList args;
    QVariant result;
    bool MetaInvoker::run();
};

#endif
