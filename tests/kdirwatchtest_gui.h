// krazy:excludeall=qclasses
/*
    SPDX-FileCopyrightText: 2006 Dirk Stoecker <kde@dstoecker.de>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#pragma once

#include <QDialog>

class QTextBrowser;

class KDirWatchTest_GUI : public QWidget
{
    Q_OBJECT
public:
    KDirWatchTest_GUI();
protected Q_SLOTS:
    void slotNewClicked();
    void slotDeleteClicked();
    void slotDir1(const QString &path);
    void slotDir2(const QString &path);
    void slotDir3(const QString &path);
    void slotDirty(const QString &);
    void slotCreated(const QString &);
    void slotDeleted(const QString &);

private:
    class QLineEdit *d;
    QString file, dir;
    class KDirWatch *w1;
    class KDirWatch *w2;
    class KDirWatch *w3;
    class QLineEdit *l1, *l2, *l3;
    QTextBrowser *m_eventBrowser;
};
