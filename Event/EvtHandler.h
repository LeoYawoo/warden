#pragma once

#include <cstdint>
#include "Common/TSLink.h"


class EvtHandler {
public:
    // Member variables
    TSLink<EvtHandler> link;

    int32_t (*func)(const void *, void *);

    void *param;
    float priority;
    int32_t marker;

    // Constructor
    EvtHandler() : func(nullptr), param(nullptr), priority(0.0f), marker(0) {}

    EvtHandler(int32_t (*handler)(const void *, void *), void* handlerParam, float prio = 0.0f)
        : func(handler), param(handlerParam), priority(prio), marker(0) {}

    // Check if handler is valid
    bool IsValid() const {
        return func != nullptr;
    }

    // Compare by priority (for sorting)
    bool operator<(const EvtHandler& other) const {
        return priority < other.priority;
    }

    bool operator>(const EvtHandler& other) const {
        return priority > other.priority;
    }

    bool operator==(const EvtHandler& other) const {
        return func == other.func && param == other.param;
    }

    bool operator!=(const EvtHandler& other) const {
        return !(*this == other);
    }

    // Invoke handler
    int32_t Invoke(const void* data) {
        if (func) {
            return func(data, param);
        }
        return 0;
    }
};


