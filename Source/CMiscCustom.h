#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CMiscCustom manages miscellaneous custom data

class CMiscCustom {
public:
    CMiscCustom();
    ~CMiscCustom();

    // Custom data operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Custom properties
    const char* GetCustomName() const;
    void SetCustomName(const char* name);

    int32_t GetCustomValue() const;
    void SetCustomValue(int32_t value);

protected:
    bool m_initialized;
    std::string m_customName;
    int32_t m_customValue;
};
