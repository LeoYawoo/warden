#include "ProfileInternal.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

ProfileInternal::ProfileInternal() : m_valid(true) {}
ProfileInternal::~ProfileInternal() {}

bool ProfileInternal::SetInternal(const char* key, const void* data, uint32_t size) {
    if (!key || !data) return false;

    InternalEntry entry;
    entry.key = key;
    entry.data = new uint8_t[size];
    entry.size = size;
    memcpy(entry.data, data, size);
    m_entries.push_back(entry);
    return true;
}

bool ProfileInternal::GetInternal(const char* key, void* data, uint32_t size) const {
    if (!key || !data) return false;

    for (const auto& entry : m_entries) {
        if (entry.key == key) {
            size_t copySize = (size < entry.size) ? size : entry.size;
            memcpy(data, entry.data, copySize);
            return true;
        }
    }
    return false;
}

bool ProfileInternal::IsValid() const {
    return m_valid;
}
