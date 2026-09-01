#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CPresenceSys manages system-level presence

namespace Tempest {
    class CPresenceSys {
    public:
        CPresenceSys();
        ~CPresenceSys();

        // Initialize presence system
        void Initialize();

        // Shutdown presence system
        void Shutdown();

        // Check if initialized
        bool IsInitialized() const;

        // Get system ID
        int GetSystemId() const;

        // Set system ID
        void SetSystemId(int id);

    private:
        int m_systemId;
        bool m_initialized;
    };
}
