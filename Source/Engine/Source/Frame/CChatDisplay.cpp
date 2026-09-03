#include "CChatDisplay.h"

// Reverse engineered from Warcraft III binary

CChatDisplay::CChatDisplay() : m_maxMessages(100), m_showTimestamps(true) {}
CChatDisplay::~CChatDisplay() {}

void CChatDisplay::AddMessage(const char* sender, const char* message, uint32_t color) {
    if (!sender || !message) return;
    ChatMessage msg;
    msg.sender = sender;
    msg.content = message;
    msg.color = color;
    m_messages.push_back(msg);
    while (m_messages.size() > m_maxMessages) {
        m_messages.erase(m_messages.begin());
    }
}

void CChatDisplay::ClearMessages() { m_messages.clear(); }

size_t CChatDisplay::GetMessageCount() const { return m_messages.size(); }

const char* CChatDisplay::GetMessageSender(size_t index) const {
    return (index < m_messages.size()) ? m_messages[index].sender.c_str() : nullptr;
}

const char* CChatDisplay::GetMessageContent(size_t index) const {
    return (index < m_messages.size()) ? m_messages[index].content.c_str() : nullptr;
}

uint32_t CChatDisplay::GetMessageColor(size_t index) const {
    return (index < m_messages.size()) ? m_messages[index].color : 0;
}

void CChatDisplay::SetMaxMessages(size_t maxMessages) { m_maxMessages = maxMessages; }
size_t CChatDisplay::GetMaxMessages() const { return m_maxMessages; }

void CChatDisplay::SetShowTimestamps(bool show) { m_showTimestamps = show; }
bool CChatDisplay::GetShowTimestamps() const { return m_showTimestamps; }
