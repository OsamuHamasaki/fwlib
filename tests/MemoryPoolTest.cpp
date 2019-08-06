/*
 * MemoryPoolTest.cpp
 *
 *  Created on: 2017/06/21
 *      Author: osamu
 */

#include "gtest/gtest.h"
#include "MemoryPool.hpp"
#include <cstdlib>

#define BYTE_SIZE_OF_BLOCK 32U
#define MAX_NUM_OF_BLOCKS 100U

class MemoryPoolTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    MemoryPool<BYTE_SIZE_OF_BLOCK> pool { 100 };
};

TEST_F(MemoryPoolTest, remainsRightAfterConstruct)
{
    EXPECT_EQ(MAX_NUM_OF_BLOCKS, pool.remains());
}

TEST_F(MemoryPoolTest, getMemoryRightAfterConstruct)
{
    void* memory = pool.getMemory();

    EXPECT_NE(nullptr, memory);
    EXPECT_EQ(MAX_NUM_OF_BLOCKS - 1, pool.remains());
}

TEST_F(MemoryPoolTest, getMaxNumOfBlocks)
{
    uint8_t* result[MAX_NUM_OF_BLOCKS];
    for (auto& each : result)
    {
        each = nullptr;
    }

    for (size_t i = 0; i < MAX_NUM_OF_BLOCKS; i++)
    {
        result[i] = static_cast<uint8_t*>(pool.getMemory());
        EXPECT_EQ((MAX_NUM_OF_BLOCKS - i - 1), pool.remains());
    }

    for (size_t i = 0; i < MAX_NUM_OF_BLOCKS - 1; i++)
    {
        for (size_t j = i + 1; j < MAX_NUM_OF_BLOCKS; j++)
        {
            EXPECT_NE(result[i], result[j]);
            EXPECT_LE(BYTE_SIZE_OF_BLOCK, static_cast<size_t>(labs(result[i] - result[j])));
        }
    }
}

TEST_F(MemoryPoolTest, getMemoryFromEmpty)
{
    for (size_t i = 0; i < MAX_NUM_OF_BLOCKS; i++)
    {
        (void)pool.getMemory();
    }

    EXPECT_EQ(nullptr, pool.getMemory());
    EXPECT_EQ(0U, pool.remains());
}

TEST_F(MemoryPoolTest, releaseMemory)
{
    void* result[MAX_NUM_OF_BLOCKS];

    for (size_t i = 0; i < MAX_NUM_OF_BLOCKS; i++)
    {
        result[i] = pool.getMemory();
    }

    pool.releaseMemory(result[MAX_NUM_OF_BLOCKS - 1]);

    EXPECT_EQ(1U, pool.remains());
    EXPECT_EQ(result[MAX_NUM_OF_BLOCKS -1], pool.getMemory());
}

TEST_F(MemoryPoolTest, releaseMemoryThenGetAgain)
{
    void* result[MAX_NUM_OF_BLOCKS];

    for (size_t i = 0; i < MAX_NUM_OF_BLOCKS; i++)
    {
        result[i] = pool.getMemory();
    }

    pool.releaseMemory(result[MAX_NUM_OF_BLOCKS - 2]);

    EXPECT_EQ(1U, pool.remains());
    EXPECT_EQ(result[MAX_NUM_OF_BLOCKS - 2], pool.getMemory());
}
