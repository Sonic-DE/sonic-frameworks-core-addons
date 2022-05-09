// SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
// SPDX-FileCopyrightText: 2022 Harald Sitter <sitter@kde.org>

#include "ksandbox.h"

#include <QFileInfo>

bool KSandbox::isInside()
{
    return isFlatpak() || isSnap();
}

bool KSandbox::isFlatpak()
{
    return QFileInfo::exists(QStringLiteral("/.flatpak-info"));
}

bool KSandbox::isSnap()
{
    return qEnvironmentVariableIsSet("SNAP");
}
