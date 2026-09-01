#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// WEPreferences manages World Editor preferences

class WEPreferences {
public:
    WEPreferences();
    ~WEPreferences();

    // Preference properties
    const char* GetPreferenceName() const;
    void SetPreferenceName(const char* name);

    // Integer preferences
    int32_t GetIntPreference(const char* key, int32_t defaultValue = 0) const;
    void SetIntPreference(const char* key, int32_t value);

    // Float preferences
    float GetFloatPreference(const char* key, float defaultValue = 0.0f) const;
    void SetFloatPreference(const char* key, float value);

    // String preferences
    const char* GetStringPreference(const char* key, const char* defaultValue = "") const;
    void SetStringPreference(const char* key, const char* value);

    // Boolean preferences
    bool GetBoolPreference(const char* key, bool defaultValue = false) const;
    void SetBoolPreference(const char* key, bool value);

    // File operations
    bool Load(const char* fileName);
    bool Save(const char* fileName);

protected:
    std::string m_prefName;
};
