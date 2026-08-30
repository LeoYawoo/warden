#pragma once

#include <cmath>
#include <algorithm>

namespace NTempest {
    class CMath {
    public:
        // Static variables
        static constexpr float PI = 3.1415927f;
        static constexpr float TWO_PI = 6.2831855f;
        static constexpr float OO_TWO_PI = 1.0f / TWO_PI;
        static constexpr float DEG_TO_RAD = PI / 180.0f;
        static constexpr float RAD_TO_DEG = 180.0f / PI;

        // Static functions
        static int32_t fint(float n) {
            return static_cast<int32_t>(n);
        }

        static int32_t fint_n(float n) {
            return n <= 0.0f ? static_cast<int32_t>(n - 0.5f) : static_cast<int32_t>(n + 0.5f);
        }

        static uint32_t fuint(float n) {
            return static_cast<uint32_t>(n);
        }

        static uint32_t fuint_n(float n) {
            return static_cast<uint32_t>(n + 0.5f);
        }

        static uint32_t fuint_pi(float n) {
            return static_cast<uint32_t>(n + 0.99994999);
        }

        static float sqrt(float x) {
            return ::sqrtf(x);
        }

        static float sin(float x) {
            return ::sinf(x);
        }

        static float cos(float x) {
            return ::cosf(x);
        }

        static float tan(float x) {
            return ::tanf(x);
        }

        static float asin(float x) {
            return ::asinf(x);
        }

        static float acos(float x) {
            return ::acosf(x);
        }

        static float atan2(float y, float x) {
            return ::atan2f(y, x);
        }

        static float Abs(float x) {
            return ::fabsf(x);
        }

        static float Min(float a, float b) {
            return a < b ? a : b;
        }

        static float Max(float a, float b) {
            return a > b ? a : b;
        }

        static float Clamp(float value, float minVal, float maxVal) {
            return value < minVal ? minVal : (value > maxVal ? maxVal : value);
        }

        static float Lerp(float a, float b, float t) {
            return a + (b - a) * t;
        }

        static float Wrap(float value, float minVal, float maxVal) {
            float range = maxVal - minVal;
            return minVal + ::fmodf(value - minVal + range, range);
        }

        static float DegToRad(float deg) {
            return deg * DEG_TO_RAD;
        }

        static float RadToDeg(float rad) {
            return rad * RAD_TO_DEG;
        }
    };
}