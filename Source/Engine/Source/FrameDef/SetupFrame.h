#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class FrameDef;

// Reverse engineered from Warcraft III binary
// SetupFrame manages frame setup operations

class SetupFrame {
public:
    SetupFrame();
    ~SetupFrame();

    // Setup properties
    int32_t GetSetupId() const;
    void SetSetupId(int32_t id);

    const char* GetSetupName() const;
    void SetSetupName(const char* name);

    // Setup state
    bool IsComplete() const;
    void SetComplete(bool complete);

    // Setup operations
    bool Setup(FrameDef* frameDef);
    void Reset();

    // Setup parameters
    void SetParameter(const char* key, const char* value);
    const char* GetParameter(const char* key) const;

protected:
    int32_t m_setupId;
    std::string m_setupName;
    bool m_complete;
    FrameDef* m_frameDef;
};
