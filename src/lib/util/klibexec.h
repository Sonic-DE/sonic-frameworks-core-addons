/*
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
    SPDX-FileCopyrightText: 2021 Harald Sitter <sitter@kde.org>
*/

#ifndef KLIBEXEC_H
#define KLIBEXEC_H

#include <kcoreaddons_export.h>

#include <QString>
#include <QStringList>

namespace KLibexec
{

KCOREADDONS_EXPORT QString pathFromAddress(const QString &relativePath, void *address);
KCOREADDONS_EXPORT QString findLibexecFromAddress(const QString &exectuableName, const QStringList &paths);

/**
 * @brief Absolute libexec path relative from the current shared object.
 *
 * This function helps locate the absolute libexec path relative to the caller's binary artifact.
 *
 * @param relativePath relative location
 * @return QString absolute libexec path or empty string if it cannot be resolved
 */
inline QString path(const QString &relativePath)
{
    // this MUST be inline so that the marker address is in the calling object!
    static int marker = 0;
    return pathFromAddress(relativePath, &marker);
}

/// TODO convenience finder appdir > qt.conf > qt.conf+kf5 (fallbacks from caller?: relative > absolute)
inline QString findLibexec(const QString &exectuableName, const QStringList &paths)
{
    // intentionally inline because libexecPath must be inline!
    return findLibexecFromAddress(exectuableName, paths);
}

} // namespace KLibexec

#endif // KLIBEXEC_H
