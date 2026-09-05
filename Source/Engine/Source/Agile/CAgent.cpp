#include "CAgent.h"

// Reverse engineered from Warcraft III binary

// CAgentBaseAbs - Address: 0x839F0F
CAgentBaseAbs::CAgentBaseAbs() {
    // Inherits from NIpse::CRlAgent
    // Virtual table set in constructor
}

CAgentBaseAbs::~CAgentBaseAbs() {
    // Virtual destructor
}

CAgentBaseAbs* CAgentBaseAbs::Constants_(CAgentBaseAbs* agent) {
    // Set constants
    *reinterpret_cast<int*>(reinterpret_cast<char*>(agent) + 12) = 727803756;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(agent) + 16) = 727803745;
    return agent;
}

// CAgent
CAgent::CAgent() : CAgentBaseAbs() {
    // Virtual table set in constructor
}

CAgent::~CAgent() {
    // Virtual destructor
}

void CAgent::BindMini(CAgentBaseAbs* base) {
    // Bind mini agent
}

// CAgentPtr
template<typename T>
CAgentPtr<T>::CAgentPtr() : m_agent(nullptr) {
}

template<typename T>
CAgentPtr<T>::~CAgentPtr() {
    Release();
}

template<typename T>
T* CAgentPtr<T>::Get() const {
    return m_agent;
}

template<typename T>
void CAgentPtr<T>::Set(T* agent) {
    if (m_agent != agent) {
        Release();
        m_agent = agent;
    }
}

template<typename T>
void CAgentPtr<T>::Release() {
    if (m_agent) {
        // Release reference
        m_agent = nullptr;
    }
}

// Explicit template instantiation
template class CAgentPtr<CAgent>;
template class CAgentPtr<void>;
