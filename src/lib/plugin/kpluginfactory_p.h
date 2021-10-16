/*
    This file is part of the KDE project

    SPDX-FileCopyrightText: 2007 Matthias Kretz <kretz@kde.org>
    SPDX-FileCopyrightText: 2007 Bernhard Loos <nhuh.put@web.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KPLUGINFACTORY_P_H
#define KPLUGINFACTORY_P_H

#include "kpluginfactory.h"
#include <KPluginMetaData>
#include <QMultiHash>

#include "kcoreaddons_debug.h"

class KPluginFactoryPrivate
{
    friend class KPluginFactory;

public:
    ~KPluginFactoryPrivate() = default;

protected:
    template<class T>
    using HashDataPair = QPair<const QMetaObject *, T>;
    using Plugin = HashDataPair<KPluginFactory::CreateInstanceFunction>;
    using PluginWithMetadata = HashDataPair<KPluginFactory::CreateInstanceWithMetaDataFunction>;

    KPluginFactoryPrivate() = default;

    KPluginMetaData metaData;
    QMultiHash<QString, Plugin> createInstanceHash;
    QMultiHash<QString, PluginWithMetadata> createInstanceWithMetaDataHash;

    template<class T>
    void insertPluginInHash(const QString &keyword,
                            const QMetaObject *metaObject,
                            QMultiHash<QString, QPair<const QMetaObject *, T>> &instanceHash,
                            const HashDataPair<T> &instancePair)
    {
        Q_ASSERT(metaObject);
        // we allow different interfaces to be registered without keyword
        if (!keyword.isEmpty()) {
            if (instanceHash.contains(keyword)) {
                qCWarning(KCOREADDONS_DEBUG) << "A plugin with the keyword" << keyword << "was already registered. A keyword must be unique!";
            }
            instanceHash.insert(keyword, instancePair);
        } else {
            const QList<HashDataPair<T>> clashes(instanceHash.values(keyword));
            const QMetaObject *superClass = metaObject->superClass();
            // check hierarchy of all registered with the same keyword registered classes
            if (superClass) {
                for (const auto &plugin : clashes) {
                    for (const QMetaObject *otherSuper = plugin.first->superClass(); otherSuper; otherSuper = otherSuper->superClass()) {
                        if (superClass == otherSuper) {
                            qCWarning(KCOREADDONS_DEBUG) << "Two plugins with the same interface(" << superClass->className()
                                                         << ") were registered. Use keywords to identify the plugins.";
                        }
                    }
                }
            }
            // check hierarchy of newly newly registered plugin against all registered classes with the same keyword
            for (const auto &plugin : clashes) {
                superClass = plugin.first->superClass();
                if (superClass) {
                    for (const QMetaObject *otherSuper = metaObject->superClass(); otherSuper; otherSuper = otherSuper->superClass()) {
                        if (superClass == otherSuper) {
                            qCWarning(KCOREADDONS_DEBUG) << "Two plugins with the same interface(" << superClass->className()
                                                         << ") were registered. Use keywords to identify the plugins.";
                        }
                    }
                }
            }
        }
        instanceHash.insert(keyword, instancePair);
    }
};

#endif // KPLUGINFACTORY_P_H
