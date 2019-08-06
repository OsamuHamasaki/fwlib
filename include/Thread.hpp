/*
 * Thread.hpp
 *
 *  Created on: 2017/07/11
 *      Author: osamu
 */

#ifndef INCLUDE_THREAD_HPP_
#define INCLUDE_THREAD_HPP_

#include <pthread.h>
#include <cstring>
#include "Uncopyable.hpp"

class Activity
{
public:
    virtual ~Activity()
    {
    }
    virtual void execute() = 0;
};

class Thread : private Uncopyable
{
private:
    pthread_t threadId;
    Activity* const activity;

    static void* startSub(void* self)
    {
        static_cast<Thread*>(self)->run();
        return nullptr;
    }

    void run()
    {
        activity->execute();
    }

public:
    Thread(const Activity& activity)
            : activity(&const_cast<Activity&>(activity))
    {
        memset(&threadId, 0, sizeof(threadId));
    }

    virtual ~Thread()
    {
    }

    void start()
    {
        pthread_create(&threadId, nullptr, startSub, (void*)this);
    }

    void join()
    {
        pthread_join(threadId, nullptr);
    }
};

#endif /* INCLUDE_THREAD_HPP_ */
