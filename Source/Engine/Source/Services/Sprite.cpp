#include "Sprite.h"

// Reverse engineered from Warcraft III binary

Sprite::Sprite()
    : m_spriteId(0), m_visible(true), m_playing(false),
      m_x(0), m_y(0), m_scaleX(1), m_scaleY(1), m_rotation(0),
      m_animList(nullptr) {}

Sprite::~Sprite() {}

int32_t Sprite::GetSpriteId() const { return m_spriteId; }
void Sprite::SetSpriteId(int32_t id) { m_spriteId = id; }
const char* Sprite::GetSpriteName() const { return m_spriteName.c_str(); }
void Sprite::SetSpriteName(const char* name) { m_spriteName = name ? name : ""; }
bool Sprite::IsVisible() const { return m_visible; }
void Sprite::SetVisible(bool visible) { m_visible = visible; }
bool Sprite::IsPlaying() const { return m_playing; }
void Sprite::SetPlaying(bool playing) { m_playing = playing; }
float Sprite::GetX() const { return m_x; }
float Sprite::GetY() const { return m_y; }
void Sprite::SetPosition(float x, float y) { m_x = x; m_y = y; }
float Sprite::GetScaleX() const { return m_scaleX; }
float Sprite::GetScaleY() const { return m_scaleY; }
void Sprite::SetScale(float x, float y) { m_scaleX = x; m_scaleY = y; }
float Sprite::GetRotation() const { return m_rotation; }
void Sprite::SetRotation(float rotation) { m_rotation = rotation; }
SprAnimList* Sprite::GetAnimList() const { return m_animList; }
void Sprite::SetAnimList(SprAnimList* animList) { m_animList = animList; }
