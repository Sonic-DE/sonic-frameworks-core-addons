#include <QStringList>

#include "kcoreaddons_export.h"

namespace KRuntimePlatform
{
/*
 * Returns the runtime platform, e.g. "desktop" or "tablet, touch". The first entry/ies in the list relate to the platform
 * formfactor and the last is the input method specialization.
 * If the string is empty, there is no specified runtime platform and a traditional desktop environment may be assumed.
 *
 * The value is read using the PLASMA_PLATFORM env variable
 */
KCOREADDONS_EXPORT QStringList runtimePlatform();
}
