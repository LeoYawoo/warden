#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

// Reverse engineered from Warcraft III binary
// CCustomData manages custom data for units

class CCustomData {
public:
    CCustomData();
    ~CCustomData();

    // Custom data operations
    bool SetData(const char* key, const char* value);
    bool GetData(const char* key, std::string& value) const;
    bool HasData(const char* key) const;
    bool RemoveData(const char* key);

    // Custom data properties
    size_t GetCount() const;
    void Clear();

protected:
    std::unordered_map<std::string, std::string> m_data;
};
