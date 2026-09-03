#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// NIpse::CRlProperty represents a reinforcement learning property

namespace NIpse {
    class CRlProperty {
    public:
        CRlProperty();
        ~CRlProperty();

        // Property properties
        int32_t GetPropertyId() const;
        void SetPropertyId(int32_t id);

        const char* GetPropertyName() const;
        void SetPropertyName(const char* name);

        // Property value
        float GetValue() const;
        void SetValue(float value);

        // Property state
        bool IsValid() const;
        void SetValid(bool valid);

    private:
        int32_t m_propertyId;
        std::string m_propertyName;
        float m_value;
        bool m_valid;
    };
}
