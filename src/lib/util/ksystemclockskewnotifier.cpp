/*
    SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "ksystemclockskewnotifier.h"
#include "ksystemclockskewnotifierengine_p.h"

class KSystemClockSkewNotifierPrivate
{
public:
    void loadNotifierEngine();
    void unloadNotifierEngine();

    KSystemClockSkewNotifier *notifier = nullptr;
    KSystemClockSkewNotifierEngine *engine = nullptr;
    bool isActive = false;
};

void KSystemClockSkewNotifierPrivate::loadNotifierEngine()
{
    engine = KSystemClockSkewNotifierEngine::create(notifier);

    if (engine) {
        QObject::connect(engine, &KSystemClockSkewNotifierEngine::skewed, notifier, &KSystemClockSkewNotifier::skewed);
    }
}

void KSystemClockSkewNotifierPrivate::unloadNotifierEngine()
{
    if (!engine) {
        return;
    }

    QObject::disconnect(engine, &KSystemClockSkewNotifierEngine::skewed, notifier, &KSystemClockSkewNotifier::skewed);
    engine->deleteLater();

    engine = nullptr;
}

KSystemClockSkewNotifier::KSystemClockSkewNotifier(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<KSystemClockSkewNotifierPrivate>())
{
    d->notifier = this;
}

KSystemClockSkewNotifier::~KSystemClockSkewNotifier()
{
}

bool KSystemClockSkewNotifier::isActive() const
{
    return d->isActive;
}

void KSystemClockSkewNotifier::setActive(bool set)
{
    if (d->isActive == set) {
        return;
    }

    d->isActive = set;

    if (d->isActive) {
        d->loadNotifierEngine();
    } else {
        d->unloadNotifierEngine();
    }

    Q_EMIT activeChanged();
}

#include "moc_ksystemclockskewnotifier.cpp"
