#include "CBlpTexture.h"
#include "StormMac/Memory.h"
#include <cstring>

// Reverse engineered from Warcraft III binary
// Address: 0x81EDFB

CBlpTexture::CBlpTexture()
    : m_textureId(0),
      m_width(0),
      m_height(0),
      m_format(0),
      m_loaded(false),
      m_data(nullptr) {
    memset(m_internal, 0, sizeof(m_internal));
}

CBlpTexture::~CBlpTexture() {
    Unload();
}

int32_t CBlpTexture::GetTextureId() const {
    return m_textureId;
}

void CBlpTexture::SetTextureId(int32_t id) {
    m_textureId = id;
}

const char* CBlpTexture::GetTextureName() const {
    return m_textureName.c_str();
}

void CBlpTexture::SetTextureName(const char* name) {
    if (name) {
        m_textureName = name;
    } else {
        m_textureName.clear();
    }
}

uint32_t CBlpTexture::GetWidth() const {
    return m_width;
}

uint32_t CBlpTexture::GetHeight() const {
    return m_height;
}

void CBlpTexture::SetSize(uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
}

uint32_t CBlpTexture::GetFormat() const {
    return m_format;
}

void CBlpTexture::SetFormat(uint32_t format) {
    m_format = format;
}

bool CBlpTexture::Load(const char* fileName) {
    if (!fileName) return false;

    Unload();
    m_textureName = fileName;

    // TODO: Implement actual BLP loading
    m_loaded = true;
    return true;
}

void CBlpTexture::Unload() {
    if (m_data) {
        SMemFree(m_data, __FILE__, __LINE__, 0);
        m_data = nullptr;
    }
    m_loaded = false;
    m_width = 0;
    m_height = 0;
}

bool CBlpTexture::IsLoaded() const {
    return m_loaded;
}
