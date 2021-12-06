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
KCOREADDONS_EXPORT QStringList pathCandidates(const QStringList &fallbackPaths);

/**
 * @brief Absolute libexec path resolved from relative path to the current shared object.
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

/// TODO convenience finder appdir > qt.conf > qt.conf+kf5 > (fallbacks from caller?: relative > absolute)
inline QString findLibexec(const QString &exectuableName, const QStringList &paths)
{
    // TODO: move to cpp I guess. since we need the relativePath passed in for path() anyway we may as well accept
    // a QStringList. to the caller it makes no difference either way
    return findLibexecFromAddress(exectuableName, paths);
}

/// TODO alternative candidate (caller gets access to the internal list and can prepend/append/qdebug/findExec it). disadvantage: callers may presume things about the list content
inline QStringList paths(const QString &relativePath)
{
    // intentional inline because path must be inline
    return pathCandidates({path(relativePath)});
}

} // namespace KLibexec

#endif // KLIBEXEC_H
