/*
    SPDX-FileCopyrightText: 2021 Alexander Lohnau <alexander.lohnau@gmx.de>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include <QObject>
#include <QtPlugin>

class MyQtPlugin : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "somepluginid")
};

#include "qtplugin.moc"
