//
// Created by steve on 21.12.19.
//

#include <cmath>

#ifndef G203_UTIL_H
#define G203_UTIL_H

/**
 * Checks if two floats are nearly the same.
 * @param f1 First float value.
 * @param f2 Second float value.
 * @param epsilon The max difference between them to be equal.
 * @return True if equal, else false.
 */
static bool IsEqual(float f1, float f2, float epsilon)
{
    if(std::abs(f1 - f2) < epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif //G203_UTIL_H
