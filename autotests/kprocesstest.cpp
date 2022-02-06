/*
    This file is part of the KDE libraries

    SPDX-FileCopyrightText: 2007 Oswald Buddenhagen <ossi@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kprocesstest_helper.h"
#include <QFile>
#include <QObject>
#include <QStandardPaths>
#include <QTest>
#include <kprocess.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

class KProcessTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void test_channels();
    void test_setShellCommand();
    void test_setProgram();
};

// IOCCC nomination pending

static QString callHelper(KProcess::OutputChannelMode how)
{
    QProcess p;
    p.setProcessChannelMode(QProcess::MergedChannels);

    QString helper = QCoreApplication::applicationDirPath() + QStringLiteral("/kprocesstest_helper");
#ifdef Q_OS_WIN
    helper += QStringLiteral(".exe");
#endif

    Q_ASSERT(QFile::exists(helper));
    p.start(helper, QStringList() << QString::number(how) << QStringLiteral("--nocrashhandler"));
    p.waitForFinished();
    return QString::fromLatin1(p.readAllStandardOutput());
}

#define EO EOUT "\n"
#define EE EERR "\n"
#define TESTCHAN(me, ms, pout, rout, rerr)                                                                                                                     \
    e = QStringLiteral("mode: " ms "\n" POUT pout ROUT rout RERR rerr);                                                                                        \
    a = QStringLiteral("mode: " ms "\n") + callHelper(KProcess::me);                                                                                           \
    QCOMPARE(a, e)

void KProcessTest::test_channels()
{
#ifdef Q_OS_UNIX
    QString e;
    QString a;
    TESTCHAN(SeparateChannels, "separate", "", EO, EE);
    TESTCHAN(ForwardedChannels, "forwarded", EO EE, "", "");
    TESTCHAN(OnlyStderrChannel, "forwarded stdout", EO, "", EE);
    TESTCHAN(OnlyStdoutChannel, "forwarded stderr", EE, EO, "");
    TESTCHAN(MergedChannels, "merged", "", EO EE, "");
#else
    Q_UNUSED(callHelper);
    QSKIP("This test needs a UNIX system");
#endif
}

void KProcessTest::test_setShellCommand()
{
    // Condition copied from kprocess.cpp
#if !defined(__linux__) && !defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__OpenBSD__) && !defined(__DragonFly__) && !defined(__GNU__)
    QSKIP("This test needs a free UNIX system");
#else
    KProcess p;

    p.setShellCommand(QStringLiteral("cat"));
    QCOMPARE(p.program().count(), 1);
    QCOMPARE(p.program().at(0), QStandardPaths::findExecutable(QStringLiteral("cat")));
    QVERIFY(p.program().at(0).endsWith(QLatin1String("/bin/cat")));
    p.setShellCommand(QStringLiteral("true || false"));
    QCOMPARE(p.program(), QStringList() << QStringLiteral("/bin/sh") << QStringLiteral("-c") << QString::fromLatin1("true || false"));
#endif
}

void KProcessTest::test_setProgram()
{
    KProcess proc;

    // Setting a program, the full path to the executable will be used if found
    proc.setProgram("true", QStringList{"--version"});
    QCOMPARE(proc.program(), (QStringList{"/usr/bin/true", "--version"}));

    // The same, but with the setProgram(QStringList) overload
    proc.setProgram(QStringList{"true", "--version"});
    QCOMPARE(proc.program(), (QStringList{"/usr/bin/true", "--version"}));

    // Setting a non-existing program, will clear the d->prog and d->args, since the executable
    // can't be found
    proc.setProgram("fooo", QStringList{"--version"});
    QCOMPARE(proc.program(), QStringList{QString()});

    // The same, but with the setProgram(QStringList) overload
    proc.setProgram(QStringList{"fooo", "--version"});
    QCOMPARE(proc.program(), QStringList{QString()});

    QTemporaryDir dir;
    const QString dirPath = dir.path();
    QVERIFY(QFile::copy("/usr/bin/true", dirPath + "/true-copy"));
    proc.setWorkingDirectory(dirPath);
    proc.setProgram("true-copy");
    // Executable in the current working dir is ignored
    QCOMPARE(proc.program(), QStringList{QString()});

    // Using the full path, the executable is found/used as expected
    proc.setProgram(dirPath + "/true-copy");
    QCOMPARE(proc.program(), QStringList{dirPath + "/true-copy"});
}

QTEST_MAIN(KProcessTest)

#include "kprocesstest.moc"
