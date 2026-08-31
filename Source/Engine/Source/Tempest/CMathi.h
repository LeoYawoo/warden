#pragma once


#include <cstdint>

namespace Tempest {
    class CMathi {
    public:
        static constexpr float PI = 3.1415927f;
        static constexpr float TWO_PI = 6.2831855f;
        static constexpr float OO_TWO_PI = 1.0f / TWO_PI;

        static int32_t fint(float n);

        static int32_t fint_n(float n);

        static uint32_t fuint(float n);

        static uint32_t fuint_n(float n);

        static uint32_t fuint_pi(float n);

        static float sqrt(float x);

        static int32_t fint_mi(float input);

        static void sincos_(float value, float &a2, float &a3);

        static void sincos_(double value, double &x_8, double &x_12);
    };
}



