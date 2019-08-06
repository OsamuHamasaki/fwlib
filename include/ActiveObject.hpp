/*
 * ActiveObject.hpp
 *
 *  Created on: 2016/12/31
 *      Author: osamu
 */

#ifndef ACTIVEOBJECT_HPP_
#define ACTIVEOBJECT_HPP_

#include "Uncopyable.hpp"
#include "Thread.hpp"

class ActiveObject : private Uncopyable, public Activity
{
private:
    Thread thread;

    void execute()
    {
        activity();
    }

    virtual void activity() = 0;

public:
    ActiveObject()
            : thread(*this)
    {
    }

    virtual ~ActiveObject()
    {
    }

    void run()
    {
        thread.start();
    }

    void join()
    {
        thread.join();
    }
};

#endif /* ACTIVEOBJECT_HPP_ */
