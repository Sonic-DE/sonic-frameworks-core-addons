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

    const QString m_relative = QStringLiteral("fakeexec/kf5");
    const QString m_fixtureName = QStringLiteral("klibexectest-fixture-binary");
    QString m_fixtureDir;
    QString m_fixturePath;

private Q_SLOTS:
    void initTestCase()
    {
        m_fixtureDir = QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + m_relative);
        m_fixturePath = QDir::cleanPath(m_fixtureDir + QDir::separator() + m_fixtureName);
        QDir().mkpath(m_fixtureDir);
        QFile fixture(m_fixturePath);
        QVERIFY(fixture.open(QFile::WriteOnly));
        fixture.setPermissions(QFile::ExeOwner);
    }

    void testPath()
    {
        QCOMPARE(KLibexec::path(m_relative), m_fixtureDir);
    }

    void testFind()
    {
        QCOMPARE(KLibexec::findLibexec(m_fixtureName, {KLibexec::path(m_relative)}), m_fixturePath);
    }
};

QTEST_MAIN(KLibexecTest)

#include "klibexectest.moc"
