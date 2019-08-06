/*
 * SharedValue.hpp
 *
 *  Created on: 2017/07/11
 *      Author: 010880016
 */

#ifndef SHAREDVALUE_HPP_
#define SHAREDVALUE_HPP_

#include "ConditionVariable.hpp"
#include "Mutex.hpp"
#include "Uncopyable.hpp"

template<class T>
class SharedValue : private Uncopyable
{
private:
    Mutex mutex;
    ConditionVariable condVar;

    virtual bool predicate() = 0;
    virtual void setValue(const T& val) = 0;
    virtual T getValue() = 0;

public:
    SharedValue()
            : mutex(), condVar()
    {
    }

    virtual ~SharedValue()
    {
    }

    void set(const T& val)
    {
        Lock lock(mutex);

        setValue(val);
        condVar.notify();
    }

    T get()
    {
        Lock lock(mutex);

        while (!predicate())
        {
            condVar.wait(mutex);
        }
        return getValue();
    }
};

#endif /* SHAREDVALUE_HPP_ */
