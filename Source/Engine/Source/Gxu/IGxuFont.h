#pragma once

#include <cstdint>

// Forward declarations
struct CGxStringBatch;

// Reverse engineered from Warcraft III binary
// IGxuFont is the interface for font rendering

class IGxuFont {
public:
    virtual ~IGxuFont() = default;

    // Font operations
    virtual bool Load(const char* fileName) = 0;
    virtual void Unload() = 0;

    // String operations
    virtual void BeginString(CGxStringBatch* batch) = 0;
    virtual void EndString() = 0;

    // Character operations
    virtual float GetCharWidth(char ch) = 0;
    virtual float GetCharHeight(char ch) = 0;

    // Font properties
    virtual float GetHeight() const = 0;
    virtual float GetScale() const = 0;
    virtual void SetScale(float scale) = 0;

protected:
    float m_height;
    float m_scale;
};
