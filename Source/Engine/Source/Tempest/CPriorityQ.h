#pragma once

#include "CDynParms.h"
#include "CDynTable.h"
#include <vector>
#include <algorithm>

// Reverse engineered from Warcraft III binary
// Address: 0x86C7C3
// CPriorityQ is a priority queue implementation

namespace Tempest {
    template<typename T>
    class CPriorityQ {
    public:
        CPriorityQ(const CDynParms& parms);
        virtual ~CPriorityQ();

        // Enqueue an item
        void Enqueue(const T& item);

        // Dequeue an item
        T Dequeue();

        // Discard all items
        void DiscardAll();

        // Check if empty
        bool IsEmpty() const;

        // Get count
        size_t GetCount() const;

    private:
        std::vector<T> m_items;
        CDynParms m_parms;
    };

    // Implementation
    template<typename T>
    CPriorityQ<T>::CPriorityQ(const CDynParms& parms) : m_parms(parms) {
    }

    template<typename T>
    CPriorityQ<T>::~CPriorityQ() {
        DiscardAll();
    }

    template<typename T>
    void CPriorityQ<T>::Enqueue(const T& item) {
        m_items.push_back(item);
        std::push_heap(m_items.begin(), m_items.end());
    }

    template<typename T>
    T CPriorityQ<T>::Dequeue() {
        if (m_items.empty()) {
            return T();
        }
        std::pop_heap(m_items.begin(), m_items.end());
        T item = m_items.back();
        m_items.pop_back();
        return item;
    }

    template<typename T>
    void CPriorityQ<T>::DiscardAll() {
        m_items.clear();
    }

    template<typename T>
    bool CPriorityQ<T>::IsEmpty() const {
        return m_items.empty();
    }

    template<typename T>
    size_t CPriorityQ<T>::GetCount() const {
        return m_items.size();
    }
}
