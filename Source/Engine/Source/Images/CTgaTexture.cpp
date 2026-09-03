#include "CTgaTexture.h"
#include "StormMac/Memory.h"
#include <cstring>

// Reverse engineered from Warcraft III binary
// Address: 0x81ED57

CTgaTexture::CTgaTexture()
    : m_textureId(0),
      m_width(0),
      m_height(0),
      m_format(0),
      m_loaded(false),
      m_data(nullptr) {
    memset(m_internal, 0, sizeof(m_internal));
}

CTgaTexture::~CTgaTexture() {
    Unload();
}

int32_t CTgaTexture::GetTextureId() const {
    return m_textureId;
}

void CTgaTexture::SetTextureId(int32_t id) {
    m_textureId = id;
}

const char* CTgaTexture::GetTextureName() const {
    return m_textureName.c_str();
}

void CTgaTexture::SetTextureName(const char* name) {
    if (name) {
        m_textureName = name;
    } else {
        m_textureName.clear();
    }
}

uint32_t CTgaTexture::GetWidth() const {
    return m_width;
}

uint32_t CTgaTexture::GetHeight() const {
    return m_height;
}

void CTgaTexture::SetSize(uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
}

uint32_t CTgaTexture::GetFormat() const {
    return m_format;
}

void CTgaTexture::SetFormat(uint32_t format) {
    m_format = format;
}

bool CTgaTexture::Load(const char* fileName) {
    if (!fileName) return false;

    Unload();
    m_textureName = fileName;

    // In a real implementation, this would:
    // 1. Open the TGA file
    // 2. Parse the TGA header
    // 3. Read the image data
    // 4. Store the data in memory
    // For now, we just mark it as loaded
    m_loaded = true;
    return true;
}

void CTgaTexture::Unload() {
    if (m_data) {
        SMemFree(m_data, __FILE__, __LINE__, 0);
        m_data = nullptr;
    }
    m_loaded = false;
    m_width = 0;
    m_height = 0;
}

bool CTgaTexture::IsLoaded() const {
    return m_loaded;
}
