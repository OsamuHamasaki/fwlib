//
// RedundantStackTest.cpp
//

#include <gtest/gtest.h>
#include <stdint.h>
#include "RedundantStack.hpp"

//
// Stack for Test Stab
//
class Stack
{
private:
    static const size_t stackSize = 200;

    uint32_t stackArea[stackSize];
    uint32_t* pStack;

public:
    Stack() : pStack(&stackArea[stackSize - 1]) {}
    ~Stack() {}
    
    void push(uint32_t value) { *pStack-- = value; }
    uint32_t pop() { return *++pStack; }

    uint32_t* getSP() { return pStack; }

    void makeNoise(int offsetFromSP, uint32_t value) { *(pStack + offsetFromSP) = value; }
};

TEST(StackTest, TestPushPop)
{
    Stack stack;

    stack.push(1);
    stack.push(2);

    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
}

TEST(StackTest, TestGetSP)
{
    Stack stack;
    uint32_t* initialSP = stack.getSP();

    stack.push(1);
    EXPECT_EQ(initialSP - 1, stack.getSP());

    stack.pop();
    EXPECT_EQ(initialSP, stack.getSP());
}

TEST(StackTest, TestMakeNoise)
{
    Stack stack;

    stack.push(1);
    stack.push(2);

    stack.makeNoise(1, 3);

    EXPECT_EQ(3U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
}

//
// Fixture
//
class RedundantStackTest : public ::testing::Test
{
protected:
    Stack stack;
    RedundantStack redundantStack;

protected:
    void SetUp() { redundantStack.initialSP(stack.getSP()); }
    void TearDown() {}
};

TEST_F(RedundantStackTest, PushPopNoMemoryError)
{
    stack.push(1);
    stack.push(2);

    redundantStack.makeRedundancy(stack.getSP());
    redundantStack.correctError();

    EXPECT_EQ(2U, stack.pop());
    EXPECT_EQ(1U, stack.pop());
}

//
// End of File
//
