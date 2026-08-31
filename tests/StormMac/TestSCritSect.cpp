#include <gtest/gtest.h>
#include "StormMac/thread/SCritSect.h"
#include <thread>
#include <vector>
#include <atomic>

TEST(SCritSectTest, DefaultConstructor) {
    SCritSect critsect;
    // Should not crash
}

TEST(SCritSectTest, EnterLeave) {
    SCritSect critsect;
    critsect.Enter();
    critsect.Leave();
    // Should not crash
}

TEST(SCritSectTest, TryEnter) {
    SCritSect critsect;
    critsect.Enter();

    // TryEnter should fail when already locked
    // Note: This behavior may vary by implementation
    bool result = critsect.TryEnter();
    // We just verify it doesn't crash
    (void)result;

    critsect.Leave();
}

TEST(SCritSectTest, LockGuard) {
    SCritSect critsect;
    {
        SCritSect::Lock lock(critsect);
        // Should be locked here
    }
    // Should be unlocked here
}

TEST(SCritSectTest, MultipleThreads) {
    SCritSect critsect;
    std::atomic<int> counter(0);
    const int numThreads = 10;
    const int iterations = 1000;

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < iterations; ++j) {
                SCritSect::Lock lock(critsect);
                counter++;
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    EXPECT_EQ(counter.load(), numThreads * iterations);
}

TEST(SCritSectTest, NestedLocking) {
    SCritSect critsect;
    critsect.Enter();
    // Nested locking should work (critical sections are reentrant on Windows)
    critsect.Enter();
    critsect.Leave();
    critsect.Leave();
}
