#pragma once


#include <windows.h>


class SCritSect {
public:
    // Member variables

    CRITICAL_SECTION m_opaqueData;

    // Member functions
    SCritSect();

    ~SCritSect();

    void Enter();

    void Leave();

    // Try to enter without blocking
    bool TryEnter();

    // RAII lock guard
    class Lock {
    public:
        explicit Lock(SCritSect &critsect) : m_critsect(critsect) {
            m_critsect.Enter();
        }

        ~Lock() {
            m_critsect.Leave();
        }

        // Non-copyable
        Lock(const Lock &) = delete;
        Lock &operator=(const Lock &) = delete;

    private:
        SCritSect &m_critsect;
    };
};


