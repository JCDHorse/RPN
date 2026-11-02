#include <gtest/gtest.h>
#include "Stack.hpp"

TEST(StackTest, IsEmptyAtConstruction) {
    Stack<int> stack;

    EXPECT_TRUE(stack.empty());
    EXPECT_FALSE(stack.full());
}

TEST(StackTest, PushMakesStackNonEmpty) {
    Stack<int> stack;

    stack.push(42);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.head(), 42);
}

TEST(StackTest, HeadReturnsLastPushedValue) {
    Stack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.head(), 30);
}

TEST(StackTest, PopReturnsLastPushedValue) {
    Stack<int> stack;

    stack.push(10);
    stack.push(20);

    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);
    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, HeadOnEmptyStackThrows) {
    Stack<int> stack;

    EXPECT_THROW(stack.head(), std::runtime_error);
}

TEST(StackTest, PopOnEmptyStackThrows) {
    Stack<int> stack;

    EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST(StackTest, CanPushBeyondInitialCapacity) {
    Stack<int> stack;

    // La capacité initiale est de 8 éléments.
    for (int i = 0; i < 100; ++i) {
        stack.push(i);
    }

    EXPECT_EQ(stack.head(), 99);

    for (int i = 99; i >= 0; --i) {
        EXPECT_EQ(stack.pop(), i);
    }

    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, WorksWithStrings) {
    Stack<std::string> stack;

    stack.push("hello");
    stack.push("world");

    EXPECT_EQ(stack.head(), "world");
    EXPECT_EQ(stack.pop(), "world");
    EXPECT_EQ(stack.pop(), "hello");
    EXPECT_TRUE(stack.empty());
}
