#include "CMessageFrame.h"

// Reverse engineered from Warcraft III binary

CMessageFrame::CMessageFrame() : m_messageType(0) {}
CMessageFrame::~CMessageFrame() {}

const char* CMessageFrame::GetMessage() const { return m_message.c_str(); }
void CMessageFrame::SetMessage(const char* message) { m_message = message ? message : ""; }

int32_t CMessageFrame::GetMessageType() const { return m_messageType; }
void CMessageFrame::SetMessageType(int32_t type) { m_messageType = type; }

void CMessageFrame::ShowMessage(const char* message, int32_t type) {
    m_message = message ? message : "";
    m_messageType = type;
    SetVisible(true);
}

void CMessageFrame::ClearMessage() {
    m_message.clear();
    m_messageType = 0;
    SetVisible(false);
}
