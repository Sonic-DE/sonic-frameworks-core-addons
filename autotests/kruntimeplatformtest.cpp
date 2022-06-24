#include "kruntimeplatform.h"
#include <QObject>
#include <QTest>

class KRuntimePlatformTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testRuntimePlatform()
    {
        qputenv("PLASMA_PLATFORM", "mobile:bigscreen");
        QStringList expected{"mobile", "bigscreen"};
        QCOMPARE(KRuntimePlatform::runtimePlatform(), expected);
    }
};

QTEST_GUILESS_MAIN(KRuntimePlatformTest)

#include "kruntimeplatformtest.moc"
