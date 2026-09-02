#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

// Reverse engineered from Warcraft III binary
// Database manages key-value data storage

class Database {
public:
    Database();
    ~Database();

    // Database operations
    bool Open(const char* fileName);
    void Close();
    bool IsOpen() const;

    // Key-value operations
    bool Get(const char* key, std::string& value) const;
    bool Set(const char* key, const char* value);
    bool Delete(const char* key);
    bool Has(const char* key) const;

    // Batch operations
    size_t Count() const;
    void Clear();

    // File operations
    bool Save(const char* fileName = nullptr);
    bool Load(const char* fileName = nullptr);

protected:
    std::string m_fileName;
    bool m_open;
    std::unordered_map<std::string, std::string> m_data;
};
