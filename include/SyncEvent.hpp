/*
 * SyncEvent.hpp
 *
 *  Created on: 2017/07/08
 *      Author: osamu
 */

#ifndef INCLUDE_SYNCEVENT_HPP_
#define INCLUDE_SYNCEVENT_HPP_

#include "SharedValue.hpp"
#include "Uncopyable.hpp"

class SyncEvent : private Uncopyable
{
private:
    class Implementation : public SharedValue<bool>
    {
    private:
        bool isNotified;

        // implementation of template methods required SharedValue
        bool predicate()
        {
            return isNotified;
        }

        void setValue(const bool&)
        {
            isNotified = true;
        }

        bool getValue()
        {
            isNotified = false;
            return false;
        }
    public:
        Implementation() : isNotified(false) {}

    };

    Implementation impl;

public:
    SyncEvent()
    {
    }

    ~SyncEvent()
    {
    }

    void wait()
    {
        (void)impl.get();
    }

    void notify()
    {
        impl.set(true);
    }
};

#endif /* INCLUDE_SYNCEVENT_HPP_ */
