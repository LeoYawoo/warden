#include "CSimpleTop.h"

// Reverse engineered from Warcraft III binary

CSimpleTop::CSimpleTop() : m_focusedFrame(nullptr) {}
CSimpleTop::~CSimpleTop() {}

void CSimpleTop::SetFocus(CSimpleFrame* frame) { m_focusedFrame = frame; }
CSimpleTop* CSimpleTop::GetTopFrame() const { return const_cast<CSimpleTop*>(this); }
