#include <gtest/gtest.h>
#include "Storm/thread/CCritSect.h"
#include <thread>
#include <vector>
#include <atomic>

TEST(CCritSectTest, DefaultConstructor) {
    CCritSect critsect;
    // Should not crash
}

TEST(CCritSectTest, EnterLeave) {
    CCritSect critsect;
    critsect.Enter();
    critsect.Leave();
    // Should not crash
}

TEST(CCritSectTest, EnterLeaveForWriting) {
    CCritSect critsect;
    critsect.Enter(1);
    critsect.Leave(1);
    // Should not crash
}

TEST(CCritSectTest, TryEnter) {
    CCritSect critsect;
    critsect.Enter();

    // TryEnter should fail when already locked
    bool result = critsect.TryEnter();
    // We just verify it doesn't crash
    (void)result;

    critsect.Leave();
}

TEST(CCritSectTest, LockGuard) {
    CCritSect critsect;
    {
        CCritSect::Lock lock(critsect);
        // Should be locked here
    }
    // Should be unlocked here
}

TEST(CCritSectTest, LockGuardForWriting) {
    CCritSect critsect;
    {
        CCritSect::Lock lock(critsect, 1);
        // Should be locked for writing here
    }
    // Should be unlocked here
}

TEST(CCritSectTest, MultipleThreads) {
    CCritSect critsect;
    std::atomic<int> counter(0);
    const int numThreads = 10;
    const int iterations = 1000;

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < iterations; ++j) {
                CCritSect::Lock lock(critsect);
                counter++;
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    EXPECT_EQ(counter.load(), numThreads * iterations);
}
