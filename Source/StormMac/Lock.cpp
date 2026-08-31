#include "Lock.h"
#include "Debug.h"
#include "Process.h"
#include "System_Lock.h"

void Blizzard::Lock::DoOnce(DoOnceData &a1, void (*a2)(void *), void *a3) {
    if (!a1.done) {
        if (Blizzard::Lock::Atomic::Increment(&a1.atomic) == 1) {
            a2(a3);
            a1.done = true;
        } else {
            while (!a1.done) {
                Blizzard::Process::Sleep(1);
            }
        }
    }
}

int32_t Blizzard::Lock::MutexCreate(Blizzard::Lock::Mutex &mutex) {

    InitializeCriticalSection(&mutex);

    return 0;

}

int32_t Blizzard::Lock::MutexEnter(Blizzard::Lock::Mutex &mutex) {

    EnterCriticalSection(&mutex);

    return 0;

}

int32_t Blizzard::Lock::MutexLeave(Blizzard::Lock::Mutex &mutex) {

    LeaveCriticalSection(&mutex);

    return 0;

}
