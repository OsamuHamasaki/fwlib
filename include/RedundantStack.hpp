//
// RedundantStack.hpp
//

#ifndef __REDUNDANTSTACK_HPP__
#define __REDUNDANTSTACK_HPP__

#include <stdint.h>

class PointerStack
{
private:
    static const size_t depth = 20;

    size_t index;
    uint32_t* pointers[depth];

public:
    PointerStack() : index(0)
    {
        for (size_t i = 0; i < depth; ++i)
        {
            pointers[i] = 0;
        }
    }

    void push(uint32_t* p)
    {
        pointers[index] = p;
        ++index;
    }

    uint32_t* pop()
    {
        --index;
        return pointers[index];
    }
};

class RedundantStack
{
private:
    uint32_t* nowSP;

    size_t index;

    static const size_t stackSize = 10;
    uint32_t copy1[stackSize];
    uint32_t copy2[stackSize];

    PointerStack spStack;

    void correctError(uint32_t* p)
    {
        if (*p != copy1[index])
        {
            if (copy1[index] == copy2[index])
            {
                *p = copy1[index];
            }
        }
    }

public:
    RedundantStack() : nowSP(0), index(stackSize - 1), spStack()
    {
        for (size_t i = 0; i < stackSize; ++i)
        {
            copy1[i] = 0;
            copy2[i] = 0;
        }
    }

    void setInitialSP(uint32_t* sp) { nowSP = sp; }

    void makeRedundancy(uint32_t* sp)
    {
        uint32_t* previousSP = nowSP;
        nowSP = sp;

        for (uint32_t* p = previousSP; sp < p; --p)
        {
            copy1[index] = copy2[index] = *p;
            --index;
        }

        spStack.push(previousSP);
    }

    void correctError()
    {
        uint32_t* previousSP = spStack.pop();
        
        for (uint32_t* p = nowSP + 1; p <= previousSP; ++p)
        {
            ++index;
            correctError(p);
        }

        nowSP = previousSP;
    }

public: // for Unit Test
    void makeNoiseToCopy1(int offset, uint32_t value)
    {
        copy1[index + offset] = value;
    }

    void makeNoiseToCopy2(int offset, uint32_t value)
    {
        copy2[index + offset] = value;
    }
};

#endif

//
// End of File
//
