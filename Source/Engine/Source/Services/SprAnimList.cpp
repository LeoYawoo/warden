#include "SprAnimList.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

SprAnimList::SprAnimList() {}
SprAnimList::~SprAnimList() { Clear(); }

void SprAnimList::AddAnim(SPRITEANIM* anim) {
    if (anim) m_anims.push_back(anim);
}

void SprAnimList::RemoveAnim(SPRITEANIM* anim) {
    auto it = std::find(m_anims.begin(), m_anims.end(), anim);
    if (it != m_anims.end()) {
        m_anims.erase(it);
    }
}

size_t SprAnimList::GetAnimCount() const {
    return m_anims.size();
}

SPRITEANIM* SprAnimList::GetAnim(size_t index) const {
    if (index < m_anims.size()) {
        return m_anims[index];
    }
    return nullptr;
}

void SprAnimList::Clear() {
    m_anims.clear();
}

bool SprAnimList::IsEmpty() const {
    return m_anims.empty();
}
