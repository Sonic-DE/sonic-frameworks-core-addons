/*
    SPDX-FileCopyrightText: 2021 Aleix Pol Gonzalez <aleixpol@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "ksignalhandler.h"
#include <QDebug>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>

int KSignalHandler::signalFd[2];

KSignalHandler::KSignalHandler()
{
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, signalFd)) {
        qWarning() << "Couldn't create a socketpair";
        return;
    }

    m_handler = new QSocketNotifier(signalFd[1], QSocketNotifier::Read, this);
    connect(m_handler, &QSocketNotifier::activated, this, &KSignalHandler::handleSignal);
}

KSignalHandler::~KSignalHandler()
{
    for (int sig : std::as_const(m_signalsRegistered)) {
        signal(sig, nullptr);
    }
    close(signalFd[0]);
    close(signalFd[1]);
}

void KSignalHandler::addSignal(int signalToTrack)
{
    m_signalsRegistered.insert(signalToTrack);
    signal(signalToTrack, signalHandler);
}

void KSignalHandler::signalHandler(int signal)
{
    ::write(signalFd[0], &signal, sizeof(signal));
}

void KSignalHandler::handleSignal()
{
    m_handler->setEnabled(false);
    int signal;
    ::read(signalFd[1], &signal, sizeof(signal));
    m_handler->setEnabled(true);

    Q_EMIT signalReceived(signal);
}

KSignalHandler *KSignalHandler::self()
{
    static KSignalHandler s_self;
    return &s_self;
}
