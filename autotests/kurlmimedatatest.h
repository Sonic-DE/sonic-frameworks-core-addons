/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2005 David Faure <faure@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class KUrlMimeDataTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testURLList();
    void testOneURL();
    void testFromQUrl();
    void testMostLocalUrlList_data();
    void testMostLocalUrlList();
};
