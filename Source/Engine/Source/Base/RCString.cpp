#include "RCString.h"
#include <cstdlib>
#include <cstring>

RCString::RCString()
    : m_str(nullptr) {
}

RCString::RCString(const char* str)
    : m_str(nullptr) {
    if (str) {
        m_str = strdup(str);
    }
}

RCString::RCString(const RCString& other)
    : m_str(nullptr) {
    if (other.m_str) {
        m_str = strdup(other.m_str);
    }
}

RCString::RCString(RCString&& other) noexcept
    : m_str(other.m_str) {
    other.m_str = nullptr;
}

RCString::~RCString() {
    Clear();
}

RCString& RCString::operator=(const char* str) {
    if (m_str != str) {
        Clear();
        if (str) {
            m_str = strdup(str);
        }
    }
    return *this;
}

RCString& RCString::operator=(const RCString& other) {
    if (this != &other) {
        Clear();
        if (other.m_str) {
            m_str = strdup(other.m_str);
        }
    }
    return *this;
}

RCString& RCString::operator=(RCString&& other) noexcept {
    if (this != &other) {
        Clear();
        m_str = other.m_str;
        other.m_str = nullptr;
    }
    return *this;
}

bool RCString::operator==(const char* str) const {
    if (!m_str && !str) return true;
    if (!m_str || !str) return false;
    return strcmp(m_str, str) == 0;
}

bool RCString::operator==(const RCString& other) const {
    return (*this) == other.m_str;
}

bool RCString::operator!=(const char* str) const {
    return !(*this == str);
}

bool RCString::operator!=(const RCString& other) const {
    return !(*this == other);
}

void RCString::Clear() {
    if (m_str) {
        free(m_str);
        m_str = nullptr;
    }
}
