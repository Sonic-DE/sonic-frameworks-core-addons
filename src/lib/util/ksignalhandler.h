/*
    SPDX-FileCopyrightText: 2021 Aleix Pol Gonzalez <aleixpol@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KSIGNALHANDLER_H
#define KSIGNALHANDLER_H

#include <QObject>
#include <QSet>
#include <QSocketNotifier>

class KSignalHandlerPrivate;

/**
 * Allows getting ANSI C signals and forward them onto the Qt eventloop.
 *
 * It's a singleton as it relies on static data getting defined.
 *
 * \code
 * {
 *   KSignalHandler::self()->addSignal(SIGTERM);
 *   connect(*   KSignalHandler::self(), &KSignalHandler::signalReceived,
 *           this, &SomeClass::handleSignal);
 *   job->start();
 * }
 * \endcode
 *
 * @since 5.92
 */
class KSignalHandler : public QObject
{
    Q_OBJECT
public:
    ~KSignalHandler() override;

    /**
     * Adds @p signal to be watched for. Once the process is notified about this signal, @m signalReceived will be emitted with the same @p signal as an
     * argument.
     *
     * @see signalReceived
     */
    void addSignal(int signal);

    /**
     * Fetches an instance we can use to register our signals.
     */
    static KSignalHandler *self();

Q_SIGNALS:
    /**
     * Notifies that @p signal is emitted.
     *
     * To catch a signal, we need to make sure it's registered using @m addSignal.
     *
     * @see addSignal
     */
    void signalReceived(int signal);

private:
    KSignalHandler();
    void handleSignal();
    static void signalHandler(int signal);

    QScopedPointer<KSignalHandlerPrivate> d;
};

#endif
