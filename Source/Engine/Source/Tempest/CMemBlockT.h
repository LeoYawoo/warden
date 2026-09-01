#pragma once

#include "CMemBlock.h"

// Reverse engineered from Warcraft III binary
// CMemBlockT is a template memory block

namespace Tempest {
    template<typename T>
    class CMemBlockT : public CMemBlock {
    public:
        CMemBlockT() : CMemBlock() {
        }

        virtual ~CMemBlockT() {
        }

        virtual void Release() {
            delete this;
        }

        // Allocate memory for T objects
        bool Allocate(size_t count) {
            return CMemBlock::Allocate(count * sizeof(T));
        }

        // Get pointer to T objects
        T* GetObjects() const {
            return reinterpret_cast<T*>(m_data);
        }

        // Get object count
        size_t GetObjectCount() const {
            return m_size / sizeof(T);
        }
    };
}
