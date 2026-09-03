#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Forward declarations
class CSimpleFrame;

// Reverse engineered from Warcraft III binary
// CLayer manages UI frame layers

class CLayer {
public:
    CLayer();
    ~CLayer();

    // Layer properties
    int32_t GetLayerId() const;
    void SetLayerId(int32_t id);

    const char* GetLayerName() const;
    void SetLayerName(const char* name);

    // Layer state
    bool IsVisible() const;
    void SetVisible(bool visible);

    // Layer operations
    void AddFrame(CSimpleFrame* frame);
    void RemoveFrame(CSimpleFrame* frame);
    size_t GetFrameCount() const;
    CSimpleFrame* GetFrame(size_t index) const;

    // Layer operations
    void Update(float deltaTime);
    void Render();

protected:
    int32_t m_layerId;
    std::string m_layerName;
    bool m_visible;
    std::vector<CSimpleFrame*> m_frames;
};
