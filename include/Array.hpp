/*
 * Array.hpp
 *
 *  Created on: 2017/07/02
 *      Author: osamu
 */

#ifndef INCLUDE_ARRAYBASE_HPP_
#define INCLUDE_ARRAYBASE_HPP_

#include <cstddef>

using std::size_t;

template<typename T>
class Array
{
private:
    size_t maxSize;
    size_t size_;
    T* data;

protected:
    Array(T* data, size_t maxSize);

public:
    typedef T* iterator;
    typedef const T* const_iterator;

    virtual ~Array();

    size_t size() const;

    T front(void) const;  // if size() == 0, result has no guarantee for exception free.
    T back(void) const;   // if size() == 0, result has no guarantee for exception free.

    void push_front(T item);
    void pop_front();
    void push_back(T item);
    void pop_back();

    T& operator[](size_t index);

    template<typename Function>
    void doForEach(Function functor) const;

    iterator begin();
    iterator end();
    const_iterator cbegin();
    const_iterator cend();
};

template<typename T>
Array<T>::Array(T* data, size_t maxSize)
        : maxSize(maxSize), size_(0), data(data)
{
}

template<typename T>
Array<T>::~Array()
{
}

template<typename T>
size_t Array<T>::size() const
{
    return size_;
}

template<typename T>
T Array<T>::front(void) const // if size() == 0, result has no guarantee for exception free.
{
    return data[0];
}

template<typename T>
T Array<T>::back(void) const // if size() == 0, result has no guarantee for exception free.
{
    return data[(size_ == 0) ? 0 : size_ - 1];
}

template<typename T>
void Array<T>::push_front(T item)
{
    if (size_ == maxSize)
        return;

    for (size_t i = size_; 0 < i; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = item;
    size_ += 1;
}

template<typename T>
void Array<T>::pop_front(void)
{
    if (size_ == 0)
        return;
    for (size_t i = 1; i < size_; i++)
    {
        data[i - 1] = data[i];
    }
    size_ -= 1;
}

template<typename T>
void Array<T>::push_back(T item)
{
    if (size_ == maxSize)
        return;

    data[size_] = item;
    size_ += 1;
}

template<typename T>
void Array<T>::pop_back(void)
{
    if (size_ == 0)
        return;
    size_ -= 1;
}

template<typename T>
T& Array<T>::operator[](size_t index)
{
    return data[index];
}

template<typename T>
template<typename Function>
void Array<T>::doForEach(Function functor) const
{
    for (size_t i = 0; i < size_; i++)
    {
        functor(data[i]);
    }
}

template<typename T>
typename Array<T>::iterator Array<T>::begin()
{
    return &data[0];
}

template<typename T>
typename Array<T>::iterator Array<T>::end()
{
    return &data[size_];
}

template<typename T>
typename Array<T>::const_iterator Array<T>::cbegin()
{
    return &data[0];
}

template<typename T>
typename Array<T>::const_iterator Array<T>::cend()
{
    return &data[size_];
}

#endif /* INCLUDE_ARRAYBASE_HPP_ */
