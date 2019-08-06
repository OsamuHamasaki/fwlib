/*
 * Uncopyable.hpp
 *
 *  Created on: 2017/07/10
 *      Author: 010880016
 */

#ifndef UNCOPYABLE_HPP_
#define UNCOPYABLE_HPP_

class Uncopyable
{
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);

protected:
    Uncopyable() {}
    ~Uncopyable() {}
};

#endif /* UNCOPYABLE_HPP_ */
