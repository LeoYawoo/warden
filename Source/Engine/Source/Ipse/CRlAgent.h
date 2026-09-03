#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CDataStore;

// Reverse engineered from Warcraft III binary
// NIpse::CRlAgent represents a reinforcement learning agent

namespace NIpse {
    class CRlAgent {
    public:
        CRlAgent();
        virtual ~CRlAgent();

        // Agent properties
        int32_t GetAgentId() const;
        void SetAgentId(int32_t id);

        const char* GetAgentName() const;
        void SetAgentName(const char* name);

        // Agent state
        bool IsInitialized() const;
        void SetInitialized(bool initialized);

        bool IsRunning() const;
        void SetRunning(bool running);

        // Agent operations
        virtual void Initialize();
        virtual void Shutdown();
        virtual void Update(float deltaTime);

        // Data operations
        virtual void Save(CDataStore& data);
        virtual void Load(CDataStore& data);

    private:
        int32_t m_agentId;
        std::string m_agentName;
        bool m_initialized;
        bool m_running;
    };
}
