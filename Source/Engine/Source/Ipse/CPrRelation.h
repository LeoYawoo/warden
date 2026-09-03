#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// NIpse::CPrRelation represents a presence relation

namespace NIpse {
    class CPrRelation {
    public:
        CPrRelation();
        virtual ~CPrRelation();

        // Relation properties
        int32_t GetRelationId() const;
        void SetRelationId(int32_t id);

        // Relation state
        bool IsEnabled() const;
        void SetEnabled(bool enabled);

        // Relation operations
        void Update(float deltaTime);
        void Reset();

    private:
        int32_t m_relationId;
        bool m_enabled;
        float m_value;
        int32_t m_state;
    };
}
