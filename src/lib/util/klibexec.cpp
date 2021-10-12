/*
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
    SPDX-FileCopyrightText: 2021 Harald Sitter <sitter@kde.org>
*/

#include "klibexec.h"
#include <config-util.h>

#if HAVE_DLADDR
#include <dlfcn.h>
#elif defined(Q_OS_WIN)
#include <windows.h>
#include <errhandlingapi.h> // TODO do we need these or is windows.h sufficient?
#include <libloaderapi.h>

#include <QVarLengthArray>
#endif

#include <QDebug>
#include <QDir>

QString libraryPathFromAddress(void *address)
{
#if HAVE_DLADDR
    Dl_info info {};
    if (dladdr(address, &info) == 0) {
        qWarning() << "Failed to match address to shared object.";
        // Do not call dlerror. It's only expected to return something useful on freebsd!
        return {};
    }
    return QString::fromLocal8Bit(info.dli_fname);
#elif defined(Q_OS_WIN)
        qWarning() << "Failed to GetModuleHandleEx" << GetLastError();
    HMODULE hModule = nullptr;
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, static_cast<LPCTSTR>(address), &hModule)) {
        return {};
    }
    if (!hModule) {
        qWarning() << "hModule null unexpectedly";
        return {};
    }

    QVarLengthArray<TCHAR, MAX_PATH> pathArray;
    DWORD pathSize = pathArray.size();
    while (pathSize == pathArray.size()) { // pathSize doesn't include the null byte on success, so this only ever true if we need to grow
        pathArray.resize(pathArray.size() + MAX_PATH);
        pathSize = GetModuleFileName(hModule, pathArray.data(), pathArray.size());
        if (pathSize == 0) {
            qWarning() << "Failed to GetModuleFileName" << GetLastError();
            return {};
        }
    }
    return QString::fromWCharArray(pathArray.data());
#else // unsupported
    return {};
#endif
}

QString KLibexec::pathFromAddress(const QString &relativePath, void *address)
{
    // presumably we get native path formats for windows, to ensure consistency run them through native separator
    // conversion
    const QString libraryPath = QDir::fromNativeSeparators(libraryPathFromAddress(address));
    const QString absoluteDirPath = QFileInfo(libraryPath).absolutePath();
    const QString libexecPath = QFileInfo(absoluteDirPath + QDir::separator() + relativePath).absoluteFilePath();
    qDebug() << libraryPath << absoluteDirPath << libexecPath;
    return libexecPath;
}

#include <QCoreApplication>
#include <QLibraryInfo>
#include <QStandardPaths>
QString KLibexec::findLibexecFromAddress(const QString &executableName, const QStringList &fallbackPaths)
{
    const QString qLibexec = QLibraryInfo::location(QLibraryInfo::LibraryExecutablesPath);
    const QString qLibexecKF5 = QDir(qLibexec).filePath(QStringLiteral("kf5"));

    const QStringList paths = {
        QCoreApplication::applicationDirPath(), // look where our application binary is located
        qLibexec, // look where libexec path is (can be set in qt.conf)
        qLibexecKF5, // on !win32 we use a kf5 suffix
    };
    return QStandardPaths::findExecutable(executableName, paths + fallbackPaths);;
}
