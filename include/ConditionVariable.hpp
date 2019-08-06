/*
 * ConditionVariable.hpp
 *
 *  Created on: 2017/07/11
 *      Author: 010880016
 */

#ifndef CONDITIONVARIABLE_HPP_
#define CONDITIONVARIABLE_HPP_

#include <pthread.h>
#include <cassert>
#include "Mutex.hpp"

class ConditionVariable
{
private:
    pthread_cond_t cv;
public:
    ConditionVariable()
    {
        int ret = pthread_cond_init(&cv, NULL);
        assert(ret == 0);
    }

    ~ConditionVariable()
    {
        pthread_cond_destroy(&cv);
    }

    void notify()
    {
        pthread_cond_signal(&cv);
    }

    void wait(Mutex& mutex)
    {
        pthread_cond_wait(&cv, mutex.naitiveHandle());
    }
};

#endif /* CONDITIONVARIABLE_HPP_ */
