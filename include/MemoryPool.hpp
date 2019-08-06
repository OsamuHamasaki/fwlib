/*
 * MemoryPool.hpp
 *
 *  Created on: 2017/06/21
 *      Author: osamu
 */

#ifndef INCLUDE_MEMORYPOOL_HPP_
#define INCLUDE_MEMORYPOOL_HPP_

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "Uncopyable.hpp"

using std::size_t;

static const size_t alinmentSize = 8;

static constexpr size_t alinedSize(size_t x)
{
    return ((x + alinmentSize - 1) / alinmentSize) * alinmentSize;
}

template<size_t blockByteSize>
class MemoryPool : private Uncopyable
{
private:
    const static size_t alinedBlockByteSize = alinedSize(blockByteSize);

    size_t maxNumOfBlocks;
    uint8_t* memoryBlocks;
    std::vector<void*> freeMemoryBlocks;

public:
    explicit MemoryPool(size_t maxNumOfBlocks);
    ~MemoryPool();

    size_t remains() const;
    void* getMemory();
    void releaseMemory(void* memoryBlock);
};

template<size_t blockByteSize>
MemoryPool<blockByteSize>::MemoryPool(size_t maxNumOfBlocks)
        : maxNumOfBlocks(maxNumOfBlocks),
          memoryBlocks(static_cast<uint8_t*>(malloc(maxNumOfBlocks * alinedBlockByteSize))),
          freeMemoryBlocks()
{
    if (memoryBlocks == nullptr)
        return;

    freeMemoryBlocks.reserve(maxNumOfBlocks);

    for (size_t i = 0; i < maxNumOfBlocks; i++)
    {
        freeMemoryBlocks.push_back(memoryBlocks + (alinedBlockByteSize * i));
    }
}

template<size_t blockByteSize>
MemoryPool<blockByteSize>::~MemoryPool()
{
    if (memoryBlocks != nullptr)
        free(memoryBlocks);
}

template<size_t blockByteSize>
size_t MemoryPool<blockByteSize>::remains() const
{
    return freeMemoryBlocks.size();
}

template<size_t blockByteSize>
void* MemoryPool<blockByteSize>::getMemory()
{
    if (freeMemoryBlocks.size() == 0)
        return nullptr;

    void* result = freeMemoryBlocks.back();
    freeMemoryBlocks.pop_back();
    return result;
}

template<size_t blockByteSize>
void MemoryPool<blockByteSize>::releaseMemory(void* memoryBlock)
{
    freeMemoryBlocks.push_back(memoryBlock);
}

#endif /* INCLUDE_MEMORYPOOL_HPP_ */
