/*
    SPDX-FileCopyrightText: 2014 Nicolás Alvarez <nicolas.alvarez@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#pragma once

#include <QWidget>

class FaceIconTest : public QWidget
{
    Q_OBJECT
public:
    FaceIconTest();

private:
    class QListWidget *listWidget;
};
