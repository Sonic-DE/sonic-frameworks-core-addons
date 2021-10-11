/*
    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
    SPDX-FileCopyrightText: 2021 Harald Sitter <sitter@kde.org>
*/

#include <QObject>
#include <QTest>

#include <KLibexec>

class KLibexecTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testPath()
    {
        const QString relative = QStringLiteral("libexec/kf5");
        const QString expected = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + relative);
        QCOMPARE(KLibexec::path(relative), expected);
    }

    void testFind()
    {
        const QString relative = QStringLiteral("libexec/kf5");
        qDebug() << KLibexec::findLibexec(QStringLiteral("some-binary"), {KLibexec::path(relative)});
    }
};

QTEST_MAIN(KLibexecTest)

#include "klibexectest.moc"
