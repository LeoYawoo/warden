#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CWorldObjects manages world objects in the game

class CWorldObjects {
public:
    CWorldObjects();
    ~CWorldObjects();

    // Object properties
    int32_t GetObjectId() const;
    void SetObjectId(int32_t id);

    const char* GetObjectName() const;
    void SetObjectName(const char* name);

    int32_t GetObjectType() const;
    void SetObjectType(int32_t type);

    // Object position
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    void SetPosition(float x, float y, float z);

    // Object rotation
    float GetRotation() const;
    void SetRotation(float rotation);

    // Object scale
    float GetScaleX() const;
    float GetScaleY() const;
    float GetScaleZ() const;
    void SetScale(float x, float y, float z);

    // Object state
    bool IsVisible() const;
    void SetVisible(bool visible);

    bool IsSelectable() const;
    void SetSelectable(bool selectable);

    // Object lifetime
    float GetLifetime() const;
    void SetLifetime(float lifetime);

    bool HasExpired() const;

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_objectId;
    std::string m_objectName;
    int32_t m_objectType;
    float m_x;
    float m_y;
    float m_z;
    float m_rotation;
    float m_scaleX;
    float m_scaleY;
    float m_scaleZ;
    bool m_visible;
    bool m_selectable;
    float m_lifetime;
    float m_age;
    CTerrain* m_terrain;
};
