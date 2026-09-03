#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>

// Forward declarations
class CSprite;

// Reverse engineered from Warcraft III binary
// CSpriteFrame displays sprites

class CSpriteFrame : public CSimpleFrame {
public:
    CSpriteFrame();
    virtual ~CSpriteFrame();

    // SpriteFrame properties
    const char* GetSpriteFile() const;
    void SetSpriteFile(const char* file);

    // SpriteFrame state
    bool IsPlaying() const;
    void SetPlaying(bool playing);

    // SpriteFrame animation
    void SetAnimation(int32_t animId);
    int32_t GetAnimation() const;

protected:
    std::string m_spriteFile;
    bool m_playing;
    int32_t m_animation;
};
