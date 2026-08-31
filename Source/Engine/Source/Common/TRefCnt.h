#pragma once

#include <cstdint>

class TRefCnt {
public:
    TRefCnt() : m_refcnt(0) {}

    virtual ~TRefCnt() = default;

    uint32_t IncrRef() {
        return ++m_refcnt;
    }

    uint32_t DecrRef() {
        uint32_t count = --m_refcnt;
        if (count == 0) {
            delete this;
        }
        return count;
    }

    uint32_t GetRefCount() const {
        return m_refcnt;
    }

protected:
    uint32_t m_refcnt = 0;
};


