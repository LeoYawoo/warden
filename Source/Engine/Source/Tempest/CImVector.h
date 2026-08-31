#pragma once

#include <cstdint>
#include <cstdlib>
#include "CMathi.h"

namespace Tempest {
    class CImVector {
    public:
        static uint32_t MakeARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
            return a << 24 | r << 16 | g << 8 | b;
        }

        CImVector *Set(const CImVector &that) {
            Tempest::CImVector *result;
            *this = that;
            return this;
        }

        CImVector *operator=(uint32_t value) {
            this->value = value;
            return this;
        }

        Tempest::CImVector *operator=(const Tempest::CImVector &that) {
            this->value = that.value;
            return this;
        }

        bool operator==(const CImVector &color) {
            return this->value == color.value;
        }

        void Set(float a, float r, float g, float b) {
            uint8_t a_ = CMathi::fuint_n(a * 255.0f);
            uint8_t r_ = CMathi::fuint_n(r * 255.0f);
            uint8_t g_ = CMathi::fuint_n(g * 255.0f);
            uint8_t b_ = CMathi::fuint_n(b * 255.0f);

            this->value = CImVector::MakeARGB(a_, r_, g_, b_);
        }

        int Gray(uint32_t value) {
            uint8_t red = value & 0xFF;
            uint8_t green = (value >> 8) & 0xFF;
            uint8_t blue = (value >> 16) & 0xFF;

            return (28 * red + 151 * green + 77 * blue) >> 8;
        }

        uint32_t Desaturate(uint32_t v3) {
            uint8_t v1 = Gray(v3);
            return (v1 << 8) | (v1 << 16) | this->value & 0xFF000000 | v1;
        }

        uint32_t Desaturate() {
            uint32_t result;
            result = Desaturate(*(uint32_t *) this);
            *(uint32_t *) this = result;
            return result;
        }

        int B_() const {
            return (uint8_t) this->b;
        }

        int R_() const {
            return (uint8_t) this->r;
        }

        int G_() const {
            return (uint8_t) this->g;
        }

        int MultiplyRGB_(const CImVector &that) {
            uint32_t result = (uint8_t) ((uint16_t) (that.B_() * this->B_() + 255) >> 8) |
                              (that.G_() * this->G_() + 255) & 0xFF00 |
                              ((uint8_t) ((uint16_t) (that.R_() * this->R_() + 255) >> 8) << 16) |
                              (*(uint32_t *) this & 0xFF000000);
            this->value = result;
            return result;
        }

    public:
        union {
            struct {
                uint8_t b;
                uint8_t g;
                uint8_t r;
                uint8_t a;
            };

            uint32_t value;
        };
    };
}


