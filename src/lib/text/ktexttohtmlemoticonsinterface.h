/*
    SPDX-FileCopyrightText: 2014 Daniel Vrátil <dvratil@redhat.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QMetaType>
#include <QStringList>

/**
 * @internal
 * Used internally by KTextToHTML, implemented by plugin, for dynamic dependency on KEmoticons
 */
class KTextToHTMLEmoticonsInterface
{
public:
    KTextToHTMLEmoticonsInterface()
    {
    }
    virtual ~KTextToHTMLEmoticonsInterface()
    {
    } // KF6 TODO: de-inline (-Wweak-vtables)

    virtual QString parseEmoticons(const QString &text, bool strictParse = false, const QStringList &exclude = QStringList()) = 0;
};

Q_DECLARE_METATYPE(KTextToHTMLEmoticonsInterface *)

#define KTEXTTOHTMLEMOTICONS_PROPERTY "KTextToHTMLEmoticons"
