#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Forward declarations
class CFramePoint;
class CLayer;

// Reverse engineered from Warcraft III binary
// CFrame is the base class for all UI frames

class CFrame {
public:
    CFrame();
    virtual ~CFrame();

    // Frame properties
    int32_t GetFrameId() const;
    void SetFrameId(int32_t id);

    const char* GetFrameName() const;
    void SetFrameName(const char* name);

    // Frame visibility
    bool IsVisible() const;
    void SetVisible(bool visible);

    // Frame position
    float GetX() const;
    float GetY() const;
    void SetPosition(float x, float y);

    // Frame size
    float GetWidth() const;
    float GetHeight() const;
    void SetSize(float width, float height);

    // Frame state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    // Frame hierarchy
    CFrame* GetParent() const;
    void SetParent(CFrame* parent);

    // Frame children
    void AddChild(CFrame* child);
    void RemoveChild(CFrame* child);
    size_t GetChildCount() const;
    CFrame* GetChild(size_t index) const;
    CFrame* GetChildByName(const char* name) const;

    // Frame operations
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual bool HandleInput(int32_t message, int32_t wParam, int32_t lParam);

protected:
    int32_t m_frameId;
    std::string m_frameName;
    bool m_visible;
    bool m_enabled;
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    CFrame* m_parent;
    std::vector<CFrame*> m_children;
};
