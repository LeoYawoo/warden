#include "WEPreferences.h"
#include <unordered_map>

// Reverse engineered from Warcraft III binary

static std::unordered_map<std::string, int32_t> s_intPrefs;
static std::unordered_map<std::string, float> s_floatPrefs;
static std::unordered_map<std::string, std::string> s_stringPrefs;
static std::unordered_map<std::string, bool> s_boolPrefs;

WEPreferences::WEPreferences() {}
WEPreferences::~WEPreferences() {}

const char* WEPreferences::GetPreferenceName() const { return m_prefName.c_str(); }
void WEPreferences::SetPreferenceName(const char* name) { m_prefName = name ? name : ""; }

int32_t WEPreferences::GetIntPreference(const char* key, int32_t defaultValue) const {
    auto it = s_intPrefs.find(key ? key : "");
    return it != s_intPrefs.end() ? it->second : defaultValue;
}

void WEPreferences::SetIntPreference(const char* key, int32_t value) {
    if (key) s_intPrefs[key] = value;
}

float WEPreferences::GetFloatPreference(const char* key, float defaultValue) const {
    auto it = s_floatPrefs.find(key ? key : "");
    return it != s_floatPrefs.end() ? it->second : defaultValue;
}

void WEPreferences::SetFloatPreference(const char* key, float value) {
    if (key) s_floatPrefs[key] = value;
}

const char* WEPreferences::GetStringPreference(const char* key, const char* defaultValue) const {
    auto it = s_stringPrefs.find(key ? key : "");
    return it != s_stringPrefs.end() ? it->second.c_str() : (defaultValue ? defaultValue : "");
}

void WEPreferences::SetStringPreference(const char* key, const char* value) {
    if (key && value) s_stringPrefs[key] = value;
}

bool WEPreferences::GetBoolPreference(const char* key, bool defaultValue) const {
    auto it = s_boolPrefs.find(key ? key : "");
    return it != s_boolPrefs.end() ? it->second : defaultValue;
}

void WEPreferences::SetBoolPreference(const char* key, bool value) {
    if (key) s_boolPrefs[key] = value;
}

bool WEPreferences::Load(const char* fileName) {
    (void)fileName;
    // TODO: Implement file loading
    return true;
}

bool WEPreferences::Save(const char* fileName) {
    (void)fileName;
    // TODO: Implement file saving
    return true;
}
