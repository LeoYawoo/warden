#include "BattleNetChat.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

BattleNetChat::BattleNetChat()
    : m_inChannel(false),
      m_maxMessages(100) {
}

BattleNetChat::~BattleNetChat() {
}

bool BattleNetChat::JoinChannel(const char* channelName) {
    if (!channelName) return false;
    m_currentChannel = channelName;
    m_inChannel = true;
    return true;
}

void BattleNetChat::LeaveChannel(const char* channelName) {
    (void)channelName;
    m_inChannel = false;
    m_currentChannel.clear();
}

void BattleNetChat::SendMessage(const char* channel, const char* message) {
    // Send a chat message to the specified channel
    // In a real implementation, this would:
    // 1. Validate the channel
    // 2. Format the message
    // 3. Send it to the Battle.net server
    // For now, we just add it to our local message list
    if (channel && message) {
        AddMessage("You", message, 0);
    }
}

const char* BattleNetChat::GetCurrentChannel() const {
    return m_currentChannel.c_str();
}

bool BattleNetChat::IsInChannel() const {
    return m_inChannel;
}

void BattleNetChat::AddMessage(const char* sender, const char* message, int32_t type) {
    if (!sender || !message) return;

    ChatMessage msg;
    msg.sender = sender;
    msg.content = message;
    msg.type = type;

    m_messages.push_back(msg);

    // Remove oldest messages if limit exceeded
    while (m_messages.size() > m_maxMessages) {
        m_messages.erase(m_messages.begin());
    }
}

size_t BattleNetChat::GetMessageCount() const {
    return m_messages.size();
}

const char* BattleNetChat::GetMessageSender(size_t index) const {
    if (index < m_messages.size()) {
        return m_messages[index].sender.c_str();
    }
    return nullptr;
}

const char* BattleNetChat::GetMessageContent(size_t index) const {
    if (index < m_messages.size()) {
        return m_messages[index].content.c_str();
    }
    return nullptr;
}

int32_t BattleNetChat::GetMessageTypes(size_t index) const {
    if (index < m_messages.size()) {
        return m_messages[index].type;
    }
    return 0;
}

void BattleNetChat::ClearMessages() {
    m_messages.clear();
}

void BattleNetChat::SetMaxMessages(size_t maxMessages) {
    m_maxMessages = maxMessages;
}

size_t BattleNetChat::GetMaxMessages() const {
    return m_maxMessages;
}
