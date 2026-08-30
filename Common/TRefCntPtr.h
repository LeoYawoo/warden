#pragma once

#include <cstdint>
#include <utility>

template<class T>
class TRefCntPtr {
public:
    TRefCntPtr() : m_ptr(nullptr) {}

    explicit TRefCntPtr(T *ptr) : m_ptr(ptr) {
        if (m_ptr) {
            m_ptr->IncrRef();
        }
    }

    TRefCntPtr(const TRefCntPtr &other) : m_ptr(other.m_ptr) {
        if (m_ptr) {
            m_ptr->IncrRef();
        }
    }

    TRefCntPtr(TRefCntPtr &&other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    ~TRefCntPtr() {
        if (m_ptr) {
            m_ptr->DecrRef();
        }
    }

    TRefCntPtr &operator=(const TRefCntPtr &other) {
        if (this != &other) {
            if (m_ptr) {
                m_ptr->DecrRef();
            }
            m_ptr = other.m_ptr;
            if (m_ptr) {
                m_ptr->IncrRef();
            }
        }
        return *this;
    }

    TRefCntPtr &operator=(TRefCntPtr &&other) noexcept {
        if (this != &other) {
            if (m_ptr) {
                m_ptr->DecrRef();
            }
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    TRefCntPtr &operator=(T *ptr) {
        if (m_ptr != ptr) {
            if (m_ptr) {
                m_ptr->DecrRef();
            }
            m_ptr = ptr;
            if (m_ptr) {
                m_ptr->IncrRef();
            }
        }
        return *this;
    }

    T *Get() const {
        return m_ptr;
    }

    T *Release() {
        T *ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    void Reset(T *ptr = nullptr) {
        if (m_ptr != ptr) {
            if (m_ptr) {
                m_ptr->DecrRef();
            }
            m_ptr = ptr;
            if (m_ptr) {
                m_ptr->IncrRef();
            }
        }
    }

    T &operator*() const {
        return *m_ptr;
    }

    T *operator->() const {
        return m_ptr;
    }

    explicit operator bool() const {
        return m_ptr != nullptr;
    }

    bool operator==(const TRefCntPtr &other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const TRefCntPtr &other) const {
        return m_ptr != other.m_ptr;
    }

    bool operator==(const T *ptr) const {
        return m_ptr == ptr;
    }

    bool operator!=(const T *ptr) const {
        return m_ptr != ptr;
    }

private:
    T *m_ptr;
};


