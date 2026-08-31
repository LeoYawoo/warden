#include "storm/thread/SThread.h"
#include "storm/Thread.h"

int32_t SThread::Create(uint32_t (*threadProc)(void *), void *param, SThread &thread, char *threadName, uint32_t a5) {
    uint32_t v8;
    auto handle = SCreateThread(threadProc, param, &v8, nullptr, nullptr);
    thread.m_opaqueData = handle;
    return handle != nullptr;
}
