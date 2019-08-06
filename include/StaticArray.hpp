/*
 * StaticArray.hpp
 *
 *  Created on: 2017/05/19
 *      Author: 010880016
 */

#ifndef STATICARRAY_HPP_
#define STATICARRAY_HPP_

#include <cstddef>
#include "Array.hpp"

template<class T, std::size_t maxSize>
class StaticArray : public Array<T>
{
private:
    T array[maxSize];
public:
    typedef typename Array<T>::iterator iterator;
    typedef typename Array<T>::const_iterator const_iterator;

    StaticArray();
};

template<class T, size_t maxSize>
StaticArray<T, maxSize>::StaticArray()
        : Array<T>(array, maxSize)
{
}

#endif /* STATICARRAY_HPP_ */
