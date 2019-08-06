/*
 * SharedQueue.hpp
 *
 *  Created on: 2017/07/11
 *      Author: 010880016
 */

#ifndef SHAREDQUEUE_HPP_
#define SHAREDQUEUE_HPP_

#include "List.hpp"
#include "Queue.hpp"
#include "SharedValue.hpp"
#include "Uncopyable.hpp"

template<class T>
class SharedQueue : private Uncopyable
{
private:
    class Implementation : public SharedValue<T>
    {
    private:
        List<T> list;
        Queue<T> queue;

        // implementation of template methods required SharedValue
        bool predicate()
        {
            return queue.size() != 0;
        }

        void setValue(const T& val)
        {
            queue.enqueue(val);
        }

        T getValue()
        {
            return queue.dequeue();
        }

    public:
        Implementation() : list(), queue(list) {}
    };

    Implementation impl;

public:
    SharedQueue()
    {
    }

    ~SharedQueue()
    {
    }

    void enqueue(const T& val)
    {
        impl.set(val);
    }

    T dequeue()
    {
        return impl.get();
    }
};

#endif /* SHAREDQUEUE_HPP_ */
