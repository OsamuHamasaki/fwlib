/*
 * QueueTest.cpp
 *
 *  Created on: 2017/07/10
 *      Author: 010880016
 */

#include "gtest/gtest.h"
#include "List.hpp"
#include "Queue.hpp"

class QueueTest : public ::testing::Test
{
protected:
    List<int> list;
    Queue<int> queue;

public:
    QueueTest() : list(), queue(list) {}

    virtual void SetUp()
    {
        list.getAllocator().resetMemory();
        list.getAllocator().initializeMemory(20);
    }

    virtual void TearDown()
    {

    }
};

TEST_F(QueueTest, enqueueAndDequeue)
{
    for (int i = 0; i < 10; i++)
    {
        queue.enqueue(i + 1);
    }

    EXPECT_EQ(10U, queue.size());

    for (int i = 0; queue.size() != 0; i++)
    {
        EXPECT_EQ(i + 1, queue.dequeue());
        EXPECT_EQ(static_cast<size_t>(10 - 1 - i), queue.size());
    }
};

// End of File
