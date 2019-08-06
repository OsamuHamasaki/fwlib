/*
 * Mutex.hpp
 *
 *  Created on: 2017/07/11
 *      Author: 010880016
 */

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <pthread.h>
#include <cassert>

class Mutex
{
private:
    pthread_mutex_t mutex;

    pthread_mutex_t* naitiveHandle()
    {
        return &mutex;
    }

    friend class ConditionVariable;

public:
    Mutex()
    {
        int ret = pthread_mutex_init(&mutex, NULL);
        assert(ret == 0);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&mutex);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }

};

class Lock
{
private:
    Mutex& mutex;

public:
    Lock(Mutex& m)
            : mutex(m)
    {
        mutex.lock();
    }

    ~Lock()
    {
        mutex.unlock();
    }
};

#endif /* MUTEX_HPP_ */
