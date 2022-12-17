/*
    This file is part of the KDE libraries

    SPDX-FileCopyrightText: 2008 Oswald Buddenhagen <ossi@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

class QString;

namespace KShell
{
QString homeDir(const QString &user);
QString quoteArgInternal(const QString &arg, bool _inquote);

}

#define PERCENT_VARIABLE QLatin1String("PERCENT_SIGN")
#define PERCENT_ESCAPE QLatin1String("%PERCENT_SIGN%")
