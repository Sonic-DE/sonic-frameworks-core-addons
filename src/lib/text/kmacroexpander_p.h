/*
    This file is part of the KDE libraries

    SPDX-FileCopyrightText: 2002-2003, 2007 Oswald Buddenhagen <ossi@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kmacroexpander.h"

class KMacroExpanderBasePrivate
{
public:
    KMacroExpanderBasePrivate(QChar c)
        : escapechar(c)
    {
    }
    QChar escapechar;
};
