#include "CDynParms.h"

// Reverse engineered from Warcraft III binary

namespace Tempest {

CDynParms::CDynParms() : m_initialSize(0), m_growSize(0), m_maxSize(0) {
}

CDynParms::CDynParms(size_t initialSize, size_t growSize, size_t maxSize)
    : m_initialSize(initialSize), m_growSize(growSize), m_maxSize(maxSize) {
}

CDynParms::~CDynParms() {
}

size_t CDynParms::GetInitialSize() const {
    return m_initialSize;
}

size_t CDynParms::GetGrowSize() const {
    return m_growSize;
}

size_t CDynParms::GetMaxSize() const {
    return m_maxSize;
}

void CDynParms::SetInitialSize(size_t size) {
    m_initialSize = size;
}

void CDynParms::SetGrowSize(size_t size) {
    m_growSize = size;
}

void CDynParms::SetMaxSize(size_t size) {
    m_maxSize = size;
}

} // namespace Tempest
