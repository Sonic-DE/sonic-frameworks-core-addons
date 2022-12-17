/*
    This file is part of the KDE project
    SPDX-FileCopyrightText: 2019 David Hallas <david@davidhallas.dk>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#pragma once

#include <QObject>

class KProcessListTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testKProcessInfoConstructionAssignment();
    void testProcessInfoList();
    void testProcessInfo();
    void testProcessInfoNotFound();
};
