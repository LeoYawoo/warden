#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// SysMessage manages system messages

class SysMessage {
public:
    SysMessage();
    ~SysMessage();

    // Message operations
    void AddMessage(const char* message, int32_t type = 0);
    void ClearMessages();

    // Message queries
    size_t GetMessageCount() const;
    const char* GetMessage(size_t index) const;
    int32_t GetMessageTypes(size_t index) const;

    // Message display
    void SetDisplayCount(size_t count);
    size_t GetDisplayCount() const;

protected:
    struct MessageEntry {
        std::string message;
        int32_t type;
    };

    std::vector<MessageEntry> m_messages;
    size_t m_displayCount;
};
