#include <gtest/gtest.h>
#include "Common/TRefCnt.h"

class TestRefCounted : public TRefCnt {
public:
    bool destroyed = false;

    ~TestRefCounted() override {
        destroyed = true;
    }
};

TEST(TRefCntTest, DefaultConstructor) {
    TestRefCounted obj;
    EXPECT_EQ(obj.GetRefCount(), 0u);
}

TEST(TRefCntTest, IncrRef) {
    TestRefCounted obj;
    obj.IncrRef();
    EXPECT_EQ(obj.GetRefCount(), 1u);
    obj.IncrRef();
    EXPECT_EQ(obj.GetRefCount(), 2u);
}

TEST(TRefCntTest, DecrRef) {
    TestRefCounted obj;
    obj.IncrRef();
    obj.IncrRef();
    obj.DecrRef();
    EXPECT_EQ(obj.GetRefCount(), 1u);
}

TEST(TRefCntTest, DecrRefToDelete) {
    TestRefCounted *obj = new TestRefCounted();
    obj->IncrRef();
    EXPECT_EQ(obj->GetRefCount(), 1u);

    // This should delete the object
    obj->DecrRef();
    // Object is deleted, don't access it
}

TEST(TRefCntTest, MultipleReferences) {
    TestRefCounted *obj = new TestRefCounted();
    obj->IncrRef();
    obj->IncrRef();
    obj->IncrRef();

    EXPECT_EQ(obj->GetRefCount(), 3u);

    obj->DecrRef();
    EXPECT_EQ(obj->GetRefCount(), 2u);

    obj->DecrRef();
    EXPECT_EQ(obj->GetRefCount(), 1u);

    // Last reference, object will be deleted
    obj->DecrRef();
}

TEST(TRefCntTest, VirtualDestructor) {
    TestRefCounted *obj = new TestRefCounted();
    obj->IncrRef();
    EXPECT_FALSE(obj->destroyed);

    obj->DecrRef();
    // Object is deleted, destructor was called
}
