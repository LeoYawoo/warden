#include <gtest/gtest.h>
#include <utility>
#include "Common/TRefCntPtr.h"
#include "Common/TRefCnt.h"

class TestRefObject : public TRefCnt {
public:
    int value = 0;

    TestRefObject() : value(0) {}
    explicit TestRefObject(int v) : value(v) {}
};

TEST(TRefCntPtrTest, DefaultConstructor) {
    TRefCntPtr<TestRefObject> ptr;
    EXPECT_EQ(ptr.Get(), nullptr);
    EXPECT_FALSE(ptr);
}

TEST(TRefCntPtrTest, PointerConstructor) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr(obj);
    EXPECT_EQ(ptr.Get(), obj);
    EXPECT_EQ(ptr->value, 42);
    EXPECT_TRUE(ptr);
}

TEST(TRefCntPtrTest, CopyConstructor) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr1(obj);
    TRefCntPtr<TestRefObject> ptr2(ptr1);

    EXPECT_EQ(ptr1.Get(), ptr2.Get());
    EXPECT_EQ(ptr2->value, 42);
}

TEST(TRefCntPtrTest, MoveConstructor) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr1(obj);
    TRefCntPtr<TestRefObject> ptr2(std::move(ptr1));

    EXPECT_EQ(ptr1.Get(), nullptr);
    EXPECT_EQ(ptr2.Get(), obj);
    EXPECT_EQ(ptr2->value, 42);
}

TEST(TRefCntPtrTest, CopyAssignment) {
    TestRefObject *obj1 = new TestRefObject(42);
    TestRefObject *obj2 = new TestRefObject(100);

    TRefCntPtr<TestRefObject> ptr1(obj1);
    TRefCntPtr<TestRefObject> ptr2(obj2);

    ptr1 = ptr2;

    EXPECT_EQ(ptr1.Get(), obj2);
    EXPECT_EQ(ptr2.Get(), obj2);
    EXPECT_EQ(ptr1->value, 100);
}

TEST(TRefCntPtrTest, MoveAssignment) {
    TestRefObject *obj1 = new TestRefObject(42);
    TestRefObject *obj2 = new TestRefObject(100);

    TRefCntPtr<TestRefObject> ptr1(obj1);
    TRefCntPtr<TestRefObject> ptr2(obj2);

    ptr1 = std::move(ptr2);

    EXPECT_EQ(ptr1.Get(), obj2);
    EXPECT_EQ(ptr2.Get(), nullptr);
    EXPECT_EQ(ptr1->value, 100);
}

TEST(TRefCntPtrTest, Reset) {
    TestRefObject *obj1 = new TestRefObject(42);
    TestRefObject *obj2 = new TestRefObject(100);

    TRefCntPtr<TestRefObject> ptr(obj1);
    EXPECT_EQ(ptr.Get(), obj1);

    ptr.Reset(obj2);
    EXPECT_EQ(ptr.Get(), obj2);
    EXPECT_EQ(ptr->value, 100);

    ptr.Reset();
    EXPECT_EQ(ptr.Get(), nullptr);
}

TEST(TRefCntPtrTest, Release) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr(obj);

    TestRefObject *released = ptr.Release();
    EXPECT_EQ(released, obj);
    EXPECT_EQ(ptr.Get(), nullptr);

    // Clean up
    delete released;
}

TEST(TRefCntPtrTest, Equality) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr1(obj);
    TRefCntPtr<TestRefObject> ptr2(obj);

    EXPECT_TRUE(ptr1 == ptr2);
    EXPECT_FALSE(ptr1 != ptr2);
}

TEST(TRefCntPtrTest, Dereference) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr(obj);

    EXPECT_EQ((*ptr).value, 42);
    EXPECT_EQ(ptr->value, 42);
}

TEST(TRefCntPtrTest, SelfAssignment) {
    TestRefObject *obj = new TestRefObject(42);
    TRefCntPtr<TestRefObject> ptr(obj);

    ptr = ptr;
    EXPECT_EQ(ptr.Get(), obj);
    EXPECT_EQ(ptr->value, 42);
}
