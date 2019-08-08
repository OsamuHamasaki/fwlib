//
// RedundantStack.hpp
//

#ifndef __REDUNDANTSTACK_HPP__
#define __REDUNDANTSTACK_HPP__

#include <stdint.h>

class RedundantStack
{
private:
    uint32_t* initialSP;
    uint32_t* nowSP;

    size_t index;

    static const size_t stackSize = 10;
    uint32_t copy[stackSize];

public:
    RedundantStack() : index(stackSize - 1)
    {
        for (size_t i = 0; i < stackSize; ++i)
        {
            copy[stackSize - 1 - i] = 0;
        }
    }

    void setInitialSP(uint32_t* sp) { initialSP = sp; }
    void makeRedundancy(uint32_t* sp)
    {
        nowSP = sp;

        for (uint32_t* p = initialSP; sp < p; --p)
        {
            copy[index] = *p;
            --index;
        }
    }

    void correctError()
    {
        for (uint32_t* p = nowSP + 1; p <= initialSP; ++p)
        {
            ++index;
            *p = copy[index];
        }
    }
};

#endif

//
// End of File
//
