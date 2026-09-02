#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// ProfileInternal manages internal profile data

class ProfileInternal {
public:
    ProfileInternal();
    ~ProfileInternal();

    // Internal data operations
    bool SetInternal(const char* key, const void* data, uint32_t size);
    bool GetInternal(const char* key, void* data, uint32_t size) const;

    // Validation
    bool IsValid() const;

protected:
    struct InternalEntry {
        std::string key;
        void* data;
        uint32_t size;
    };

    std::vector<InternalEntry> m_entries;
    bool m_valid;
};
