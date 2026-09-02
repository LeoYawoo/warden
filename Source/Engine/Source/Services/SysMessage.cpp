#include "SysMessage.h"

// Reverse engineered from Warcraft III binary

SysMessage::SysMessage() : m_displayCount(10) {}
SysMessage::~SysMessage() {}

void SysMessage::AddMessage(const char* message, int32_t type) {
    if (message) {
        m_messages.push_back({message, type});
        if (m_messages.size() > m_displayCount) {
            m_messages.erase(m_messages.begin());
        }
    }
}

void SysMessage::ClearMessages() {
    m_messages.clear();
}

size_t SysMessage::GetMessageCount() const {
    return m_messages.size();
}

const char* SysMessage::GetMessage(size_t index) const {
    if (index < m_messages.size()) {
        return m_messages[index].message.c_str();
    }
    return nullptr;
}

int32_t SysMessage::GetMessageTypes(size_t index) const {
    if (index < m_messages.size()) {
        return m_messages[index].type;
    }
    return 0;
}

void SysMessage::SetDisplayCount(size_t count) {
    m_displayCount = count;
}

size_t SysMessage::GetDisplayCount() const {
    return m_displayCount;
}
