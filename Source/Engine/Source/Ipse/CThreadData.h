#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// NIpse::CThreadData manages thread-specific data

namespace NIpse {
    class CThreadData {
    public:
        CThreadData();
        ~CThreadData();

        // Thread data properties
        int32_t GetThreadId() const;
        void SetThreadId(int32_t id);

        // Thread data state
        bool IsValid() const;
        void SetValid(bool valid);

        // Thread data operations
        void Initialize();
        void Shutdown();

    private:
        int32_t m_threadId;
        bool m_valid;
        void* m_data;
    };
}
