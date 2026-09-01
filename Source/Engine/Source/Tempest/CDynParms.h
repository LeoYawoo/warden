#pragma once

#include <cstdint>
#include <cstddef>

// Reverse engineered from Warcraft III binary
// CDynParms holds dynamic allocation parameters

namespace Tempest {
    class CDynParms {
    public:
        CDynParms();
        CDynParms(size_t initialSize, size_t growSize, size_t maxSize);
        ~CDynParms();

        // Get initial size
        size_t GetInitialSize() const;

        // Get grow size
        size_t GetGrowSize() const;

        // Get max size
        size_t GetMaxSize() const;

        // Set initial size
        void SetInitialSize(size_t size);

        // Set grow size
        void SetGrowSize(size_t size);

        // Set max size
        void SetMaxSize(size_t size);

    private:
        size_t m_initialSize;
        size_t m_growSize;
        size_t m_maxSize;
    };
}
