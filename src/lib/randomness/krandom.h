/*
    This file is part of the KDE libraries

    SPDX-FileCopyrightText: 1999 Matthias Kalle Dalheimer <kalle@kde.org>
    SPDX-FileCopyrightText: 2000 Charles Samuels <charles@kde.org>
    SPDX-FileCopyrightText: 2005 Joseph Wenninger <kde@jowenn.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KRANDOM_H
#define KRANDOM_H

#include <kcoreaddons_export.h>

#include <QRandomGenerator>
#include <QString>

#include <limits>

/**
 * \headerfile krandom.h <KRandom>
 *
 * @short Helper class to create random data
 *
 * This namespace provides methods which generate random data.
 * KRandom is not recommended for serious random-number generation needs,
 * like cryptography.
 */
namespace KRandom
{
#if KCOREADDONS_ENABLE_DEPRECATED_SINCE(5, 72)
/**
 * Generates a uniform random number.
 * @return A random number in the range [0, RAND_MAX). The RNG is seeded
 *   on first use.
 * @deprecated Since 5.72, use QRandomGenerator::global(). The 1:1 port is bounded(RAND_MAX) but check all the methods that QRandomGenerator provides.
 */
KCOREADDONS_DEPRECATED_VERSION(5, 72, "Use QRandomGenerator::global(). The 1:1 port is bounded(RAND_MAX) but check see all the methods that QRandomGenerator provides.")
KCOREADDONS_EXPORT int random();
#endif

/**
 * Generates a random string.  It operates in the range [A-Za-z0-9]
 * @param length Generate a string of this length.
 * @return the random string
 */
KCOREADDONS_EXPORT QString randomString(int length);

/**
 * Put a container in random order.
 *
 * The container needs to implement size() and T &operator[]
 *
 * @since 5.73
 */
template<typename T>
KCOREADDONS_EXPORT void randomize(T &container)
{
    randomize(container, QRandomGenerator::global());
}

/**
 * Put a container in random order using the given random number generator.
 *
 * The container needs to implement size() and T &operator[]
 *
 * @since 5.73
 */
template<typename T>
KCOREADDONS_EXPORT void randomize(T &container, QRandomGenerator *generator)
{
    if (container.size() == 0)
        return;

    Q_ASSERT(container.size() <= std::numeric_limits<int>::max());
    // Fisher-Yates algorithm
    for (int index = container.size() - 1; index > 0; --index) {
        const int swapIndex = generator->bounded(index + 1);
        qSwap(container[index], container[swapIndex]);
    }
}

}

#endif

