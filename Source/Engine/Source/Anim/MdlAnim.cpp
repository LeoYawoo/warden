#include "MdlAnim.h"

// Reverse engineered from Warcraft III binary

MdlAnim::MdlAnim()
    : m_animId(0), m_duration(0.0f), m_playing(false), m_currentTime(0.0f) {
}

MdlAnim::~MdlAnim() {}

int32_t MdlAnim::GetAnimId() const { return m_animId; }
void MdlAnim::SetAnimId(int32_t id) { m_animId = id; }

const char* MdlAnim::GetAnimName() const { return m_animName.c_str(); }
void MdlAnim::SetAnimName(const char* name) { m_animName = name ? name : ""; }

float MdlAnim::GetDuration() const { return m_duration; }
void MdlAnim::SetDuration(float duration) { m_duration = duration; }

bool MdlAnim::IsPlaying() const { return m_playing; }
void MdlAnim::SetPlaying(bool playing) { m_playing = playing; }

void MdlAnim::Update(float deltaTime) {
    if (m_playing) {
        m_currentTime += deltaTime;
        if (m_currentTime >= m_duration) {
            m_currentTime = 0.0f;
        }
    }
}

void MdlAnim::Reset() {
    m_currentTime = 0.0f;
    m_playing = false;
}
