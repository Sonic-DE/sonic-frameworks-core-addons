#include "kruntimeplatform.h"

QStringList KRuntimePlatform::runtimePlatform()
{
    const QString env = QString::fromLocal8Bit(getenv("PLASMA_PLATFORM"));
    return QStringList(env.split(QLatin1Char(':'), Qt::SkipEmptyParts));
}
