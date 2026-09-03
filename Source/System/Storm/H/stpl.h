#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// stpl provides Storm template library functions

namespace Storm {
    // Template functions
    template<typename T>
    void Swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    template<typename T>
    const T& Min(const T& a, const T& b) {
        return (a < b) ? a : b;
    }

    template<typename T>
    const T& Max(const T& a, const T& b) {
        return (a > b) ? a : b;
    }

    template<typename T>
    const T& Clamp(const T& value, const T& minVal, const T& maxVal) {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }
}
