#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// BattleNetChat manages Battle.net chat functionality

class BattleNetChat {
public:
    BattleNetChat();
    ~BattleNetChat();

    // Chat operations
    bool JoinChannel(const char* channelName);
    void LeaveChannel(const char* channelName);
    void SendMessage(const char* channel, const char* message);

    // Chat properties
    const char* GetCurrentChannel() const;
    bool IsInChannel() const;

    // Chat history
    void AddMessage(const char* sender, const char* message, int32_t type = 0);
    size_t GetMessageCount() const;
    const char* GetMessageSender(size_t index) const;
    const char* GetMessageContent(size_t index) const;
    int32_t GetMessageTypes(size_t index) const;

    // Chat management
    void ClearMessages();
    void SetMaxMessages(size_t maxMessages);
    size_t GetMaxMessages() const;

protected:
    struct ChatMessage {
        std::string sender;
        std::string content;
        int32_t type;
    };

    std::string m_currentChannel;
    bool m_inChannel;
    std::vector<ChatMessage> m_messages;
    size_t m_maxMessages;
};
