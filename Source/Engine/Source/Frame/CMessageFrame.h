#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CMessageFrame displays messages

class CMessageFrame : public CSimpleFrame {
public:
    CMessageFrame();
    virtual ~CMessageFrame();

    // Message properties
    const char* GetMessage() const;
    void SetMessage(const char* message);

    // Message type
    int32_t GetMessageType() const;
    void SetMessageType(int32_t type);

    // Message display
    void ShowMessage(const char* message, int32_t type = 0);
    void ClearMessage();

protected:
    std::string m_message;
    int32_t m_messageType;
};
