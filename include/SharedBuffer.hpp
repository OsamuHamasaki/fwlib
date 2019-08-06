/*
 * SharedBuffer.hpp
 *
 *  Created on: 2017/07/06
 *      Author: 010880016
 */

#ifndef SHAREDBUFFER_HPP_
#define SHAREDBUFFER_HPP_

#include <cstddef>
#include <vector>
#include "Uncopyable.hpp"

using std::size_t;

class SharedBufferEntity;

class SharedBuffer
{
private:
    SharedBufferEntity* bufferEntity;

    void referBuffer();
    void unreferBuffer();

public:
    SharedBuffer()
            : bufferEntity(nullptr)
    {
    }

    explicit SharedBuffer(SharedBufferEntity* bufferEntity)
            : bufferEntity(bufferEntity)
    {
        referBuffer();
    }

    ~SharedBuffer()
    {
        unreferBuffer();
    }

    SharedBuffer(const SharedBuffer& other)
            : bufferEntity(other.bufferEntity)
    {
        referBuffer();
    }

    SharedBuffer& operator=(const SharedBuffer& other);

    uint8_t& operator[](size_t index) const;
    uint8_t* get() const;

    void release();
};

class SharedBufferPool : private Uncopyable
{
private:
    uint8_t* buffer;
    std::vector<SharedBufferEntity> bufferEntities;
    std::vector<SharedBufferEntity*> freeBufferEntities;

public:
    SharedBufferPool(size_t byteSizeOfBuffer, size_t numberOfBuffers);
    ~SharedBufferPool();

    size_t capacity() const;
    size_t remains() const;
    SharedBuffer getBuffer();
    void release(SharedBufferEntity* bufferEntity);
};

#endif /* SHAREDBUFFER_HPP_ */
