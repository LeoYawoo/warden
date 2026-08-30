#pragma once

#include <cstdint>
#include <windows.h>


class CCritSect {
public:
    // Member functions
    CCritSect();

    ~CCritSect();

    void Enter();

    void Enter(int32_t forWriting);

    void Leave();

    void Leave(int32_t fromWriting);

    // Try to enter without blocking
    bool TryEnter();

    // RAII lock guard
    class Lock {
    public:
        explicit Lock(CCritSect &critsect, int32_t forWriting = 0)
            : m_critsect(critsect), m_forWriting(forWriting) {
            m_critsect.Enter(m_forWriting);
        }

        ~Lock() {
            m_critsect.Leave(m_forWriting);
        }

        // Non-copyable
        Lock(const Lock &) = delete;
        Lock &operator=(const Lock &) = delete;

    private:
        CCritSect &m_critsect;
        int32_t m_forWriting;
    };

private:
    // Member variables
    CRITICAL_SECTION m_critsect;
};


