/*
    SPDX-FileCopyrightText: 2013 Sebastian Kügler <sebas@kde.org>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include <QObject>

class JsonPlugin : public QObject
{
    Q_OBJECT

public:
    explicit JsonPlugin(QObject *parent, const QVariantList &args);
};
