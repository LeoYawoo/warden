#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainTextures manages terrain texture operations

class CTerrainTextures {
public:
    CTerrainTextures();
    ~CTerrainTextures();

    // Texture properties
    int32_t GetTextureId() const;
    void SetTextureId(int32_t id);

    const char* GetTextureName() const;
    void SetTextureName(const char* name);

    // Texture state
    bool IsActive() const;
    void SetActive(bool active);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_textureId;
    std::string m_textureName;
    bool m_active;
    CTerrain* m_terrain;
};
