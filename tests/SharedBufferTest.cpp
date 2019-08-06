/*
 * SharedBufferTest.cpp
 *
 *  Created on: 2017/07/06
 *      Author: 010880016
 */

#include "gtest/gtest.h"

#include "SharedBuffer.hpp"
#include "ActiveObject.hpp"
#include "SyncEvent.hpp"

#define NUMBER_OF_BUFFERS 5U
#define BYTE_SIZE_OF_BUFFER 10U

class SharedBufferTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
    }

    SharedBufferPool bufferPool { BYTE_SIZE_OF_BUFFER, NUMBER_OF_BUFFERS} ;
};

TEST_F(SharedBufferTest, initialize)
{
    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.capacity());
    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
}

TEST_F(SharedBufferTest, getBuffer)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    EXPECT_EQ(NUMBER_OF_BUFFERS -1 , bufferPool.remains());
}

TEST_F(SharedBufferTest, writeDataInBuffer)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer[i] = i + 1;
    }

    EXPECT_EQ(NUMBER_OF_BUFFERS -1 , bufferPool.remains());

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 1, buffer[i]);
    }
}

TEST_F(SharedBufferTest, writeDataInBuffer2)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer[i] = i + 1;
    }

    EXPECT_EQ(NUMBER_OF_BUFFERS -1 , bufferPool.remains());

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 1, buffer.get()[i]);
    }
}

TEST_F(SharedBufferTest, copyBuffer)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer[i] = i + 1;
    }

    SharedBuffer buffer2 = buffer;

    EXPECT_EQ(NUMBER_OF_BUFFERS -1 , bufferPool.remains());

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 1, buffer[i]);
        EXPECT_EQ(i + 1, buffer2[i]);
    }
}

TEST_F(SharedBufferTest, copyBufferAccessSameRAWBuffer)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer[i] = i;
    }

    SharedBuffer buffer2 = buffer;

    EXPECT_EQ(NUMBER_OF_BUFFERS -1 , bufferPool.remains());

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer[i] = i + 100;
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 100, buffer[i]);
        EXPECT_EQ(i + 100, buffer2[i]);
    }
}

TEST_F(SharedBufferTest, eachBufferAccessDiffernetRAWBuffer)
{
    SharedBuffer buffer0 = bufferPool.getBuffer();
    SharedBuffer buffer1 = bufferPool.getBuffer();
    SharedBuffer buffer2 = bufferPool.getBuffer();
    SharedBuffer buffer3 = bufferPool.getBuffer();
    SharedBuffer buffer4 = bufferPool.getBuffer();

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer0[i] = i;
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer1[i] = i + 10;
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer2[i] = i + 20;
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer3[i] = i + 30;
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer4[i] = i + 40;
    }

    EXPECT_EQ(NUMBER_OF_BUFFERS - 5 , bufferPool.remains());

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i, buffer0[i]);
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 10, buffer1[i]);
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 20, buffer2[i]);
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 30, buffer3[i]);
    }

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 40, buffer4[i]);
    }
}

TEST_F(SharedBufferTest, defaultConstruct)
{
    SharedBuffer buffer;

    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
}

TEST_F(SharedBufferTest, copyAssignment)
{
    SharedBuffer buffer;

    buffer = bufferPool.getBuffer();

    EXPECT_EQ(NUMBER_OF_BUFFERS - 1, bufferPool.remains());
}

TEST_F(SharedBufferTest, copyAssignment2)
{
    SharedBuffer buffer;
    SharedBuffer buffer2;

    buffer = bufferPool.getBuffer();
    buffer2 = bufferPool.getBuffer();

    EXPECT_EQ(NUMBER_OF_BUFFERS - 2, bufferPool.remains());

    buffer = buffer2;
    EXPECT_EQ(NUMBER_OF_BUFFERS - 1, bufferPool.remains());
}

TEST_F(SharedBufferTest, release)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    buffer.release();

    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
}

TEST_F(SharedBufferTest, reset2)
{
    SharedBuffer buffer;

    buffer.release();

    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
}

TEST_F(SharedBufferTest, getBufferOverCapacity)
{
    SharedBuffer buffer[NUMBER_OF_BUFFERS + 1];

    for (size_t i = 0; i < NUMBER_OF_BUFFERS + 1; i++)
    {
        buffer[i] = bufferPool.getBuffer();
    }

    EXPECT_EQ(0U, bufferPool.remains());
}

TEST_F(SharedBufferTest, copyConstructor)
{
    SharedBuffer buffer(bufferPool.getBuffer());
    SharedBuffer buffer2(buffer);

    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        buffer[i] = i + 1;
    }

    EXPECT_EQ(NUMBER_OF_BUFFERS - 1, bufferPool.remains());
    for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
    {
        EXPECT_EQ(i + 1, buffer2[i]);
    }
}

TEST_F(SharedBufferTest, copyConstructor2)
{
    SharedBuffer buffer;
    SharedBuffer buffer2(buffer);

    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
}

TEST_F(SharedBufferTest, getFromDefaultSmartBuffer)
{
    SharedBuffer buffer;

    EXPECT_EQ(nullptr, buffer.get());
}

class Reader : public ActiveObject
{
private:
    SharedBuffer buffer;
    SyncEvent event;

    void activity()
    {
        event.wait();

        for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
        {
            EXPECT_EQ(i + 1, buffer[i]);
        }

        buffer.release();
    }

public:
    Reader() : buffer(), event()
    {
    }

    void putBuffer(const SharedBuffer& buffer)
    {
        this->buffer = buffer;
        event.notify();
    }
};

class Writer : public ActiveObject
{
private:
    SharedBuffer buffer;
    Reader* reader;
public:
    Writer(const SharedBuffer& buffer, Reader* reader) :  buffer(buffer), reader(reader) {}

    void activity()
    {
        for (size_t i = 0; i < BYTE_SIZE_OF_BUFFER; i++)
        {
            buffer[i] = i + 1;
        }
        reader->putBuffer(buffer);

        buffer.release();
    }
};

TEST_F(SharedBufferTest, SharingBufferAnotherThread)
{
    SharedBuffer buffer = bufferPool.getBuffer();

    Reader reader;
    Writer writer(buffer, &reader);
    buffer.release();

    EXPECT_EQ(NUMBER_OF_BUFFERS - 1, bufferPool.remains());

    reader.run();
    writer.run();

    reader.join();
    writer.join();

    EXPECT_EQ(NUMBER_OF_BUFFERS, bufferPool.remains());
}

// End of File
