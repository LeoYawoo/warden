#include "CSpriteFrame.h"

// Reverse engineered from Warcraft III binary

CSpriteFrame::CSpriteFrame() : m_playing(false), m_animation(0) {}
CSpriteFrame::~CSpriteFrame() {}

const char* CSpriteFrame::GetSpriteFile() const { return m_spriteFile.c_str(); }
void CSpriteFrame::SetSpriteFile(const char* file) { m_spriteFile = file ? file : ""; }

bool CSpriteFrame::IsPlaying() const { return m_playing; }
void CSpriteFrame::SetPlaying(bool playing) { m_playing = playing; }

void CSpriteFrame::SetAnimation(int32_t animId) { m_animation = animId; }
int32_t CSpriteFrame::GetAnimation() const { return m_animation; }
