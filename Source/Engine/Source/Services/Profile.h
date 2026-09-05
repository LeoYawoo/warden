#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <fstream>

// Reverse engineered from Warcraft III binary
// Profile manages user profile data

class Profile {
public:
    Profile();
    ~Profile();

    // Profile operations
    bool Load(const char* fileName);
    bool Save(const char* fileName = nullptr);
    void Clear();

    // Profile properties
    const char* GetProfileName() const;
    void SetProfileName(const char* name);

    const char* GetFileName() const;
    bool IsLoaded() const;

    // Data operations
    bool Get(const char* key, std::string& value) const;
    bool Set(const char* key, const char* value);
    bool Has(const char* key) const;
    size_t Count() const;

protected:
    std::string m_profileName;
    std::string m_fileName;
    bool m_loaded;
    std::unordered_map<std::string, std::string> m_data;
};
