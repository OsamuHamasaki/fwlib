//
// RingBufferTest.cpp
//

#include <gtest/gtest.h>
#include "RingBuffer.hpp"
class RingBufferTest : public ::testing::Test
{
protected:
    RingBuffer<int, 2> buffer;
};

TEST_F(RingBufferTest, testAddOneValue1)
{
    buffer.addLast(1);

    EXPECT_EQ(1, buffer.getFirst());
}

TEST_F(RingBufferTest, testAddOneValue2)
{
    buffer.addLast(2);

    EXPECT_EQ(2, buffer.getFirst());
}

TEST_F(RingBufferTest, testAddTwoValue2)
{
    buffer.addLast(1);
    buffer.addLast(2);

    EXPECT_EQ(1, buffer.getFirst());
    EXPECT_EQ(2, buffer.getFirst());
}

//
// Enf of File
//

