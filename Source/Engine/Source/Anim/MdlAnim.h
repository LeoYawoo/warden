#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// MdlAnim manages model animations

class MdlAnim {
public:
    MdlAnim();
    ~MdlAnim();

    // Animation properties
    int32_t GetAnimId() const;
    void SetAnimId(int32_t id);

    const char* GetAnimName() const;
    void SetAnimName(const char* name);

    float GetDuration() const;
    void SetDuration(float duration);

    // Animation state
    bool IsPlaying() const;
    void SetPlaying(bool playing);

    // Animation operations
    void Update(float deltaTime);
    void Reset();

protected:
    int32_t m_animId;
    std::string m_animName;
    float m_duration;
    bool m_playing;
    float m_currentTime;
};
