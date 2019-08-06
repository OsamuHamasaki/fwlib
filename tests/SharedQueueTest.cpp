/*
 * SharedQueueTest.cpp
 *
 *  Created on: 2017/07/11
 *      Author: 010880016
 */

#include "gtest/gtest.h"
#include "ActiveObject.hpp"
#include "SharedQueue.hpp"
#include <thread>
#include <chrono>

class Consumer : public ActiveObject
{
private:
    SharedQueue<int> queue;

    void activity()
    {
        int i = 0;
        for (int val = -1; (val = queue.dequeue()) != -1; i++)
        {
            EXPECT_EQ(i, val);
        }
        EXPECT_EQ(20, i);
    }

public:
    Consumer()
            : queue()
    {
    }

    void putVal(int x)
    {
        queue.enqueue(x);
    }
};

class Producer : public ActiveObject
{
private:
    Consumer* consumer;

    void activity()
    {
        for (int i = 0; i < 20; i++)
        {
            consumer->putVal(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        consumer->putVal(-1);
    }

public:
    Producer(Consumer* consumer)
            : consumer(consumer)
    {
    }
};

TEST(SharedQueueTest, ProducerAndConsumer)
{
    FixedSizeAllocator<List<int>::ListNode_type> allocator;
    allocator.resetMemory();
    allocator.initializeMemory(50);

    Consumer consumer;
    Producer producer(&consumer);

    consumer.run();
    producer.run();

    consumer.join();
    producer.join();

}

// End of File
