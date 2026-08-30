#include <gtest/gtest.h>
#include "Agile/Integer.h"

TEST(IntegerTest, DefaultConstructor) {
    Integer i;
    EXPECT_EQ(i.GetValue(), 0);
}

TEST(IntegerTest, ValueConstructor) {
    Integer i(42);
    EXPECT_EQ(i.GetValue(), 42);
}

TEST(IntegerTest, SetValue) {
    Integer i;
    i.SetValue(100);
    EXPECT_EQ(i.GetValue(), 100);
}

TEST(IntegerTest, Declare) {
    Integer i;
    i.Declare(1, 2, 3, 4, 5, 6);
    // Declare should not change the value
    EXPECT_EQ(i.GetValue(), 0);
}

TEST(IntegerTest, AddAssign) {
    Integer a(10);
    a += 5;
    EXPECT_EQ(a.GetValue(), 15);
}

TEST(IntegerTest, SubtractAssign) {
    Integer a(10);
    a -= 5;
    EXPECT_EQ(a.GetValue(), 5);
}

TEST(IntegerTest, MultiplyAssign) {
    Integer a(5);
    a *= 3;
    EXPECT_EQ(a.GetValue(), 15);
}

TEST(IntegerTest, DivideAssign) {
    Integer a(10);
    a /= 2;
    EXPECT_EQ(a.GetValue(), 5);
}

TEST(IntegerTest, DivideByZero) {
    Integer a(10);
    a /= 0;
    EXPECT_EQ(a.GetValue(), 10);  // Should remain unchanged
}

TEST(IntegerTest, PreIncrement) {
    Integer a(5);
    Integer &b = ++a;
    EXPECT_EQ(a.GetValue(), 6);
    EXPECT_EQ(&b, &a);  // Should return reference to same object
}

TEST(IntegerTest, PostIncrement) {
    Integer a(5);
    Integer b = a++;
    EXPECT_EQ(a.GetValue(), 6);
    EXPECT_EQ(b.GetValue(), 5);  // Should return old value
}

TEST(IntegerTest, PreDecrement) {
    Integer a(5);
    Integer &b = --a;
    EXPECT_EQ(a.GetValue(), 4);
    EXPECT_EQ(&b, &a);
}

TEST(IntegerTest, PostDecrement) {
    Integer a(5);
    Integer b = a--;
    EXPECT_EQ(a.GetValue(), 4);
    EXPECT_EQ(b.GetValue(), 5);
}

TEST(IntegerTest, Add) {
    Integer a(10);
    Integer b = a + 5;
    EXPECT_EQ(b.GetValue(), 15);
}

TEST(IntegerTest, Subtract) {
    Integer a(10);
    Integer b = a - 5;
    EXPECT_EQ(b.GetValue(), 5);
}

TEST(IntegerTest, Equality) {
    Integer a(10);
    Integer b(10);
    Integer c(20);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(IntegerTest, Inequality) {
    Integer a(10);
    Integer b(20);
    EXPECT_TRUE(a != b);
}

TEST(IntegerTest, LessThan) {
    Integer a(5);
    Integer b(10);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(IntegerTest, GreaterThan) {
    Integer a(10);
    Integer b(5);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TEST(IntegerTest, ImplicitConversion) {
    Integer i(42);
    int val = i;
    EXPECT_EQ(val, 42);
}

TEST(IntegerTest, ChainedOperations) {
    Integer a(10);
    a += 5;
    a -= 3;
    a *= 2;
    a /= 2;
    EXPECT_EQ(a.GetValue(), 12);
}
