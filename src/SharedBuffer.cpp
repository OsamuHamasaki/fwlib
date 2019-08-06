/*
 * SharedBuffer.cpp
 *
 *  Created on: 2017/07/06
 *      Author: 010880016
 */

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>
#include "SharedBuffer.hpp"

using std::size_t;

class SharedBufferEntity
{
private:
    size_t referenceCounter;
    SharedBufferPool* const bufferPool;

public:
    uint8_t* const buffer;

    SharedBufferEntity(uint8_t* buffer, SharedBufferPool* bufferPool)
            : referenceCounter(0), bufferPool(bufferPool), buffer(buffer)
    {
    }

    ~SharedBufferEntity()
    {
    }

    void refered();
    void unrefered();
};

void SharedBufferEntity::refered()
{
    referenceCounter++; // TODO this action must be atomic.
}

void SharedBufferEntity::unrefered() // this action must be atomic.
{
    referenceCounter--;
    if (referenceCounter == 0)
    {
        bufferPool->release(this);
    }
}

void SharedBuffer::referBuffer()
{
    if (bufferEntity != nullptr) bufferEntity->refered();
}

void SharedBuffer::unreferBuffer()
{
    if (bufferEntity != nullptr) bufferEntity->unrefered();
}

SharedBuffer& SharedBuffer::operator=(const SharedBuffer& other)
{
    SharedBufferEntity* temp = bufferEntity;
    bufferEntity = other.bufferEntity;
    referBuffer();
    if (temp != nullptr)
    {
        temp->unrefered();
    }

    return *this;
}

uint8_t& SharedBuffer::operator[](size_t index) const
{
    return bufferEntity->buffer[index];
}

 uint8_t* SharedBuffer::get() const
 {
    return bufferEntity != nullptr ? bufferEntity->buffer : nullptr;
 }

void SharedBuffer::release()
{
    if (bufferEntity != nullptr)
    {
        bufferEntity->unrefered();
        bufferEntity = nullptr;
    }
}

SharedBufferPool::SharedBufferPool(size_t byteSizeOfBuffer, size_t numberOfBuffers)
        : buffer(static_cast<uint8_t*>(malloc(byteSizeOfBuffer * numberOfBuffers))),
          bufferEntities(), freeBufferEntities()
{
    if (buffer == nullptr) return;

    bufferEntities.reserve(numberOfBuffers);
    freeBufferEntities.reserve(numberOfBuffers);

    for (size_t i = 0; i < numberOfBuffers; i++)
    {
        bufferEntities.push_back(SharedBufferEntity(buffer + (i * byteSizeOfBuffer), this));
    }

    for (size_t i = 0; i < numberOfBuffers; i++)
    {
        freeBufferEntities.push_back(&bufferEntities[i]);
    }
}

SharedBufferPool::~SharedBufferPool()
{
    if (buffer != nullptr)
    {
        free(buffer);
    }
}

size_t SharedBufferPool::capacity() const
{
    return bufferEntities.size();
}

size_t SharedBufferPool::remains() const
{
    return freeBufferEntities.size();
}

SharedBuffer SharedBufferPool::getBuffer()  // TODO this action must be atomic
{
    SharedBufferEntity* bufferEntity = nullptr;
    if (!freeBufferEntities.empty())
    {
        bufferEntity = freeBufferEntities.back();
        freeBufferEntities.pop_back();
    }
    return SharedBuffer(bufferEntity);
}

void SharedBufferPool::release(SharedBufferEntity* bufferEntity)  // TODO this action must be atomic
{
    freeBufferEntities.push_back(bufferEntity);
}

// End of File
