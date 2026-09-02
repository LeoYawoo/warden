#pragma once

#include "IFrameDef.h"
#include <cstdint>
#include <string>

// Forward declarations
class CFrame;

// Reverse engineered from Warcraft III binary
// FrameDef manages frame definitions

class FrameDef : public IFrameDef {
public:
    FrameDef();
    virtual ~FrameDef();

    // IFrameDef interface
    const char* GetName() const override;
    void SetName(const char* name) override;

    int32_t GetType() const override;
    void SetType(int32_t type) override;

    bool IsEnabled() const override;
    void SetEnabled(bool enabled) override;

    CFrame* CreateFrame() override;
    void DestroyFrame(CFrame* frame) override;

    // Additional properties
    int32_t GetFrameId() const;
    void SetFrameId(int32_t id);

    const char* GetParentName() const;
    void SetParentName(const char* name);

    // Frame hierarchy
    FrameDef* GetParent() const;
    void SetParent(FrameDef* parent);

    FrameDef* GetChild() const;
    void SetChild(FrameDef* child);

    FrameDef* GetNext() const;
    void SetNext(FrameDef* next);

protected:
    int32_t m_frameId;
    std::string m_parentName;
    FrameDef* m_parent;
    FrameDef* m_child;
    FrameDef* m_next;
};
