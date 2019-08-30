//
// Ecc.cpp
//

#include "Ecc.hpp"

template <typename T>
Ecc<T>& Ecc<T>::operator=(const T& data)
{
    original = copy1 = copy2 = data;
    correctError();
    return *this;
}

template <typename T>
Ecc<T>& Ecc<T>::operator=(const Ecc<T>& other)
{
    original = other.original;
    copy1 = other.copy1;
    copy2 = other.copy2;
    correctError();
    return *this;
}

template <typename T>
Ecc<T>::operator T()
{
    correctError();
    return original;
}

template <typename T>
void Ecc<T>::correctError()
{
    if (original != copy1)
    {
        if (original == copy2)
        {
            copy1 = original;
        }
        else if (copy1 == copy2)
        {
            original = copy1;
        }
        else
        {
            /* can't correct */
        }
    }
    else if (original != copy2)
    {
        copy2 = original;
    }
    else
    {
        /* no need to correct */
    }
}

template class Ecc<int>;

// End of File

