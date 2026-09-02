#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CFrame;

// Reverse engineered from Warcraft III binary
// IFrameDef is the interface for frame definitions

class IFrameDef {
public:
    virtual ~IFrameDef() = default;

    // Frame definition properties
    virtual const char* GetName() const = 0;
    virtual void SetName(const char* name) = 0;

    virtual int32_t GetType() const = 0;
    virtual void SetType(int32_t type) = 0;

    // Frame definition state
    virtual bool IsEnabled() const = 0;
    virtual void SetEnabled(bool enabled) = 0;

    // Frame creation
    virtual CFrame* CreateFrame() = 0;
    virtual void DestroyFrame(CFrame* frame) = 0;

protected:
    std::string m_name;
    int32_t m_type;
    bool m_enabled;
};
