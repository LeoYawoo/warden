#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class SprAnimList;

// Reverse engineered from Warcraft III binary
// Sprite manages sprite rendering

class Sprite {
public:
    Sprite();
    ~Sprite();

    // Sprite properties
    int32_t GetSpriteId() const;
    void SetSpriteId(int32_t id);

    const char* GetSpriteName() const;
    void SetSpriteName(const char* name);

    // Sprite state
    bool IsVisible() const;
    void SetVisible(bool visible);

    bool IsPlaying() const;
    void SetPlaying(bool playing);

    // Sprite position
    float GetX() const;
    float GetY() const;
    void SetPosition(float x, float y);

    // Sprite scale
    float GetScaleX() const;
    float GetScaleY() const;
    void SetScale(float x, float y);

    // Sprite rotation
    float GetRotation() const;
    void SetRotation(float rotation);

    // Animation
    SprAnimList* GetAnimList() const;
    void SetAnimList(SprAnimList* animList);

protected:
    int32_t m_spriteId;
    std::string m_spriteName;
    bool m_visible;
    bool m_playing;
    float m_x;
    float m_y;
    float m_scaleX;
    float m_scaleY;
    float m_rotation;
    SprAnimList* m_animList;
};
