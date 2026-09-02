#include "Database.h"
#include <fstream>

// Reverse engineered from Warcraft III binary

Database::Database() : m_open(false) {}
Database::~Database() { Close(); }

bool Database::Open(const char* fileName) {
    if (!fileName) return false;
    m_fileName = fileName;
    m_open = true;
    return true;
}

void Database::Close() {
    m_open = false;
    m_data.clear();
}

bool Database::IsOpen() const {
    return m_open;
}

bool Database::Get(const char* key, std::string& value) const {
    if (!key) return false;
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        value = it->second;
        return true;
    }
    return false;
}

bool Database::Set(const char* key, const char* value) {
    if (!key || !value) return false;
    m_data[key] = value;
    return true;
}

bool Database::Delete(const char* key) {
    if (!key) return false;
    return m_data.erase(key) > 0;
}

bool Database::Has(const char* key) const {
    if (!key) return false;
    return m_data.find(key) != m_data.end();
}

size_t Database::Count() const {
    return m_data.size();
}

void Database::Clear() {
    m_data.clear();
}

bool Database::Save(const char* fileName) {
    (void)fileName;
    // TODO: Implement file saving
    return true;
}

bool Database::Load(const char* fileName) {
    (void)fileName;
    // TODO: Implement file loading
    return true;
}
