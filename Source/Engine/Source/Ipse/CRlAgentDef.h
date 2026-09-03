#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// NIpse::CRlAgentDef represents a reinforcement learning agent definition

namespace NIpse {
    class CRlAgentDef {
    public:
        CRlAgentDef();
        virtual ~CRlAgentDef();

        // Definition properties
        int32_t GetDefId() const;
        void SetDefId(int32_t id);

        const char* GetDefName() const;
        void SetDefName(const char* name);

        // Definition state
        bool IsValid() const;
        void SetValid(bool valid);

        // Definition operations
        void Reset();
        void Clear();

    private:
        int32_t m_defId;
        std::string m_defName;
        bool m_valid;
    };
}
