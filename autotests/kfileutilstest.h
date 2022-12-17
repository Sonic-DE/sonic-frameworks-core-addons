/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2000-2005 David Faure <faure@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class KFileUtilsTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSuggestName_data();
    void testSuggestName();
    void testfindAllUniqueFiles();
};
