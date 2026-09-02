#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
struct SPRITEANIM;

// Reverse engineered from Warcraft III binary
// SprAnimList manages sprite animation lists

class SprAnimList {
public:
    SprAnimList();
    ~SprAnimList();

    // Animation list operations
    void AddAnim(SPRITEANIM* anim);
    void RemoveAnim(SPRITEANIM* anim);
    size_t GetAnimCount() const;

    // Animation access
    SPRITEANIM* GetAnim(size_t index) const;

    // List operations
    void Clear();
    bool IsEmpty() const;

protected:
    std::vector<SPRITEANIM*> m_anims;
};
