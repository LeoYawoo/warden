#pragma once

#include <cstdint>
#include <cstring>
#include <cstdlib>

// Reverse engineered from Warcraft III binary
// CMemBlock manages memory blocks

namespace Tempest {
    class CMemBlock {
    public:
        CMemBlock() : m_data(nullptr), m_size(0), m_capacity(0) {
        }

        virtual ~CMemBlock() {
            Clear();
        }

        virtual void Release() {
            delete this;
        }

        // Allocate memory block
        bool Allocate(size_t size) {
            Clear();
            m_data = static_cast<uint8_t*>(std::malloc(size));
            if (m_data) {
                m_size = 0;
                m_capacity = size;
                return true;
            }
            return false;
        }

        // Clear memory block
        void Clear() {
            if (m_data) {
                std::free(m_data);
                m_data = nullptr;
            }
            m_size = 0;
            m_capacity = 0;
        }

        // Get data pointer
        uint8_t* GetData() const {
            return m_data;
        }

        // Get size
        size_t GetSize() const {
            return m_size;
        }

        // Get capacity
        size_t GetCapacity() const {
            return m_capacity;
        }

        // Set size
        void SetSize(size_t size) {
            if (size <= m_capacity) {
                m_size = size;
            }
        }

    protected:
        uint8_t* m_data;
        size_t m_size;
        size_t m_capacity;
    };
}
