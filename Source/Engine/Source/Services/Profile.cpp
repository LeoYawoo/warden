#include "Profile.h"

// Reverse engineered from Warcraft III binary

Profile::Profile() : m_loaded(false) {}
Profile::~Profile() { Clear(); }

bool Profile::Load(const char* fileName) {
    if (!fileName) return false;
    m_fileName = fileName;
    m_loaded = true;
    return true;
}

bool Profile::Save(const char* fileName) {
    (void)fileName;
    // TODO: Implement file saving
    return true;
}

void Profile::Clear() {
    m_data.clear();
    m_loaded = false;
}

const char* Profile::GetProfileName() const {
    return m_profileName.c_str();
}

void Profile::SetProfileName(const char* name) {
    if (name) m_profileName = name;
}

const char* Profile::GetFileName() const {
    return m_fileName.c_str();
}

bool Profile::IsLoaded() const {
    return m_loaded;
}

bool Profile::Get(const char* key, std::string& value) const {
    if (!key) return false;
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        value = it->second;
        return true;
    }
    return false;
}

bool Profile::Set(const char* key, const char* value) {
    if (!key || !value) return false;
    m_data[key] = value;
    return true;
}

bool Profile::Has(const char* key) const {
    if (!key) return false;
    return m_data.find(key) != m_data.end();
}

size_t Profile::Count() const {
    return m_data.size();
}
