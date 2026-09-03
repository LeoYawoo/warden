#include "CModelFrame.h"

// Reverse engineered from Warcraft III binary

CModelFrame::CModelFrame() : m_playing(false), m_animation(0), m_scale(1.0f) {}
CModelFrame::~CModelFrame() {}

const char* CModelFrame::GetModelFile() const { return m_modelFile.c_str(); }
void CModelFrame::SetModelFile(const char* file) { m_modelFile = file ? file : ""; }

bool CModelFrame::IsPlaying() const { return m_playing; }
void CModelFrame::SetPlaying(bool playing) { m_playing = playing; }

void CModelFrame::SetAnimation(int32_t animId) { m_animation = animId; }
int32_t CModelFrame::GetAnimation() const { return m_animation; }

float CModelFrame::GetScale() const { return m_scale; }
void CModelFrame::SetScale(float scale) { m_scale = scale; }
