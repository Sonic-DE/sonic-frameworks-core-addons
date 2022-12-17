/*
    SPDX-FileCopyrightText: 2013 Sebastian Kügler <sebas@kde.org>
    SPDX-FileCopyrightText: 2014 Alex Merry <alexmerry@kde.org>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include <QObject>

class MultiPlugin1 : public QObject
{
    Q_OBJECT

public:
    MultiPlugin1(QObject *parent, const QVariantList &args);
};

class MultiPlugin2 : public QObject
{
    Q_OBJECT

public:
    MultiPlugin2(QObject *parent, const QVariantList &args);
};
