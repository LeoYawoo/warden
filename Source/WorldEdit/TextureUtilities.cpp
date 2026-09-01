#include "TextureUtilities.h"
#include <unordered_map>
#include <cstring>

// Reverse engineered from Warcraft III binary

struct TextureData {
    uint32_t width;
    uint32_t height;
    uint32_t format;
    std::string name;
    uint8_t* data;
};

static std::unordered_map<uint32_t, TextureData> s_textures;
static uint32_t s_nextTextureId = 1;

uint32_t TextureUtilities::LoadTexture(const char* fileName) {
    if (!fileName) {
        return 0;
    }

    // TODO: Implement actual texture loading
    uint32_t id = s_nextTextureId++;
    TextureData& tex = s_textures[id];
    tex.name = fileName;
    tex.width = 0;
    tex.height = 0;
    tex.format = FORMAT_RGBA8;
    tex.data = nullptr;

    return id;
}

void TextureUtilities::UnloadTexture(uint32_t textureId) {
    auto it = s_textures.find(textureId);
    if (it != s_textures.end()) {
        if (it->second.data) {
            delete[] it->second.data;
        }
        s_textures.erase(it);
    }
}

uint32_t TextureUtilities::GetTextureWidth(uint32_t textureId) {
    auto it = s_textures.find(textureId);
    if (it != s_textures.end()) {
        return it->second.width;
    }
    return 0;
}

uint32_t TextureUtilities::GetTextureHeight(uint32_t textureId) {
    auto it = s_textures.find(textureId);
    if (it != s_textures.end()) {
        return it->second.height;
    }
    return 0;
}

const char* TextureUtilities::GetTextureName(uint32_t textureId) {
    auto it = s_textures.find(textureId);
    if (it != s_textures.end()) {
        return it->second.name.c_str();
    }
    return nullptr;
}

bool TextureUtilities::SaveTexture(uint32_t textureId, const char* fileName) {
    (void)textureId;
    (void)fileName;
    // TODO: Implement texture saving
    return false;
}

bool TextureUtilities::CopyTexture(uint32_t srcId, uint32_t dstId) {
    auto srcIt = s_textures.find(srcId);
    auto dstIt = s_textures.find(dstId);
    if (srcIt != s_textures.end() && dstIt != s_textures.end()) {
        dstIt->second.width = srcIt->second.width;
        dstIt->second.height = srcIt->second.height;
        dstIt->second.format = srcIt->second.format;
        return true;
    }
    return false;
}

uint32_t TextureUtilities::CreateTexture(uint32_t width, uint32_t height, uint32_t format) {
    uint32_t id = s_nextTextureId++;
    TextureData& tex = s_textures[id];
    tex.width = width;
    tex.height = height;
    tex.format = format;
    tex.data = new uint8_t[width * height * 4];
    memset(tex.data, 0, width * height * 4);

    return id;
}

uint32_t TextureUtilities::CreateTextureFromData(const void* data, uint32_t width, uint32_t height, uint32_t format) {
    uint32_t id = CreateTexture(width, height, format);
    if (id && data) {
        TextureData& tex = s_textures[id];
        memcpy(tex.data, data, width * height * 4);
    }
    return id;
}
