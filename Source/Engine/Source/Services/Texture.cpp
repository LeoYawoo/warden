#include "Texture.h"

// Reverse engineered from Warcraft III binary

Texture::Texture()
    : m_textureId(0), m_width(0), m_height(0), m_format(0), m_loaded(false) {}

Texture::~Texture() {}

int32_t Texture::GetTextureId() const { return m_textureId; }
void Texture::SetTextureId(int32_t id) { m_textureId = id; }
const char* Texture::GetTextureName() const { return m_textureName.c_str(); }
void Texture::SetTextureName(const char* name) { m_textureName = name ? name : ""; }
uint32_t Texture::GetWidth() const { return m_width; }
uint32_t Texture::GetHeight() const { return m_height; }
void Texture::SetSize(uint32_t width, uint32_t height) { m_width = width; m_height = height; }
uint32_t Texture::GetFormat() const { return m_format; }
void Texture::SetFormat(uint32_t format) { m_format = format; }

bool Texture::Load(const char* fileName) {
    if (!fileName) return false;
    m_textureName = fileName;
    m_loaded = true;
    return true;
}

void Texture::Unload() {
    m_loaded = false;
}

bool Texture::IsLoaded() const {
    return m_loaded;
}
