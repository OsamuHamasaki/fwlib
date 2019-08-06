/*
 * FixedSizeAllocator.hpp
 *
 *  Created on: 2017/07/02
 *      Author: osamu
 */

#ifndef INCLUDE_FIXEDSIZEALLOCATOR_HPP_
#define INCLUDE_FIXEDSIZEALLOCATOR_HPP_

#include <cstddef>
#include "MemoryPool.hpp"

template<class T>
class FixedSizeAllocator
{
private:
    static const size_t defaultMaxNumOfBlocks = 100;

    static MemoryPool<sizeof(T)>* memoryPool;

public:
    void initializeMemory(size_t maxNumOfBlocks = defaultMaxNumOfBlocks);
    void resetMemory();

    void* allocate();
    void deallocate(void* memoryBlock);

    size_t remains() const;
};

template<class T>
MemoryPool<sizeof(T)>* FixedSizeAllocator<T>::memoryPool = nullptr;

template<class T>
void FixedSizeAllocator<T>::initializeMemory(size_t maxNumOfBlocks)
{
    if (memoryPool == nullptr)
    {
        memoryPool = new MemoryPool<sizeof(T)>(maxNumOfBlocks);
    }
}

template<class T>
void FixedSizeAllocator<T>::resetMemory()
{
    if (memoryPool != nullptr)
    {
        delete memoryPool;
        memoryPool = nullptr;
    }
}

template<class T>
void* FixedSizeAllocator<T>::allocate()
{
    return memoryPool != nullptr ? memoryPool->getMemory() : nullptr;
}

template<class T>
void FixedSizeAllocator<T>::deallocate(void* memoryBlock)
{
    if (memoryPool != nullptr)
    {
        memoryPool->releaseMemory(memoryBlock);
    }
}

template<class T>
size_t FixedSizeAllocator<T>::remains() const
{
    return memoryPool != nullptr ? memoryPool->remains() : 0;
}

#endif /* INCLUDE_FIXEDSIZEALLOCATOR_HPP_ */
