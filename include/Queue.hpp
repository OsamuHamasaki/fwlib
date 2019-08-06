/*
 * Queue.hpp
 *
 *  Created on: 2017/07/10
 *      Author: 010880016
 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

template<class T, class Container = List<T> >
class Queue
{
private:
    Container& list;
public:
    Queue(Container& list)
            : list(list)
    {
    }

    void enqueue(T val)
    {
        list.push_back(val);
    }

    T dequeue()
    {
        T result = list.front();
        list.pop_front();
        return result;
    }

    size_t size()
    {
        return list.size();
    }
};

#endif /* QUEUE_HPP_ */
