/*
    This file is part of the KDE libraries

    SPDX-FileCopyrightText: 2011 David Faure <faure@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only
*/

#ifndef KFILESYSTEMTYPE_P_H
#define KFILESYSTEMTYPE_P_H

#include <kcoreaddons_export.h>

#include <QString>

/**
 * @namespace KFileSystemType
 * Provides utility functions for the type of file systems.
 */
namespace KFileSystemType
{
enum Type {
    Unknown,
    Nfs, ///< NFS or other full-featured networked filesystems (autofs, subfs, cachefs, sshfs)
    Smb, ///< SMB/CIFS mount (networked but with some FAT-like behavior)
    Fat, ///< FAT or similar (msdos, fat, vfat)
    Ramfs, ///< RAMDISK mount
    Other, ///< ext, reiser, and so on. "Normal" local filesystems.
    Ntfs, ///< @since 5.85 NTFS filesystem
};

/**
 * For a given @p path, returns the filesystem type, one of @ref KFileSystemType::Type
 * values. If the type can't be determined, @c KFileSystemType::Unknown is returned.
 *
 * @since 5.0
 */
KCOREADDONS_EXPORT Type fileSystemType(const QString &path);

/**
 * For a given @p path, returns the filesystem type name, e.g. (NFS, SMB, FAT).
 * If the filesystem type couldn't be determined, "Unknown" is returned.
 *
 * @see @ref KFileSystemType::Type
 *
 * @since 5.85
 */
KCOREADDONS_EXPORT QString fileSystemTypeName(const QString &path);
}

#endif
