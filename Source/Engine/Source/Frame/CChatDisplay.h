#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CChatDisplay displays chat messages

class CChatDisplay : public CSimpleFrame {
public:
    CChatDisplay();
    virtual ~CChatDisplay();

    // Chat operations
    void AddMessage(const char* sender, const char* message, uint32_t color = 0xFFFFFFFF);
    void ClearMessages();

    // Chat properties
    size_t GetMessageCount() const;
    const char* GetMessageSender(size_t index) const;
    const char* GetMessageContent(size_t index) const;
    uint32_t GetMessageColor(size_t index) const;

    // Chat settings
    void SetMaxMessages(size_t maxMessages);
    size_t GetMaxMessages() const;

    void SetShowTimestamps(bool show);
    bool GetShowTimestamps() const;

protected:
    struct ChatMessage {
        std::string sender;
        std::string content;
        uint32_t color;
    };

    std::vector<ChatMessage> m_messages;
    size_t m_maxMessages;
    bool m_showTimestamps;
};
