#pragma once

#include "event/Types.h"
#include "Common/TSLink.h"
#include "Common/instance/TExtraInstanceRecyclable.h"
#include <cstring>

class EvtMessage : public TExtraInstanceRecyclable<EvtMessage> {
public:
    // Member variables
    TSLink<EvtMessage> link;
    EVENTID id;
    char data[4];

    // Constructor
    EvtMessage() : id(EVENT_ID_0) {
        std::memset(data, 0, sizeof(data));
    }

    EvtMessage(EVENTID eventId) : id(eventId) {
        std::memset(data, 0, sizeof(data));
    }

    EvtMessage(EVENTID eventId, const void* eventData, size_t dataSize) : id(eventId) {
        std::memset(data, 0, sizeof(data));
        if (eventData && dataSize > 0) {
            size_t copySize = (dataSize < sizeof(data)) ? dataSize : sizeof(data);
            std::memcpy(data, eventData, copySize);
        }
    }

    // Template constructor for typed data
    template<typename T>
    EvtMessage(EVENTID eventId, const T& eventData) : id(eventId) {
        std::memset(data, 0, sizeof(data));
        if (sizeof(T) <= sizeof(data)) {
            std::memcpy(data, &eventData, sizeof(T));
        }
    }

    // Get data as typed pointer
    template<typename T>
    const T* GetData() const {
        return reinterpret_cast<const T*>(data);
    }

    template<typename T>
    T* GetData() {
        return reinterpret_cast<T*>(data);
    }

    // Check if message has valid data
    bool HasData() const {
        return id != EVENT_ID_0;
    }

    // Clear message
    void Clear() {
        id = EVENT_ID_0;
        std::memset(data, 0, sizeof(data));
    }
};


