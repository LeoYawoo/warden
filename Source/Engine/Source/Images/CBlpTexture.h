#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CTexture;

// Reverse engineered from Warcraft III binary
// Address: 0x81EDFB
// CBlpTexture represents a BLP texture

class CBlpTexture {
public:
    CBlpTexture();
    virtual ~CBlpTexture();

    // Texture properties
    int32_t GetTextureId() const;
    void SetTextureId(int32_t id);

    const char* GetTextureName() const;
    void SetTextureName(const char* name);

    // Texture dimensions
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    void SetSize(uint32_t width, uint32_t height);

    // Texture format
    uint32_t GetFormat() const;
    void SetFormat(uint32_t format);

    // Texture operations
    bool Load(const char* fileName);
    void Unload();

    // Texture state
    bool IsLoaded() const;

protected:
    int32_t m_textureId;
    std::string m_textureName;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_format;
    bool m_loaded;
    void* m_data;
    char m_internal[32];
};
