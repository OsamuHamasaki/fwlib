/*
 * Ecc.hpp
 *
 *  Created on: 2019/07/25
 *      Author: 010880016
 */

#ifndef ECC_HPP_
#define ECC_HPP_

template <typename T> // T must be bool, pointer or a kind of Integer type
class Ecc
{
public:
    // constructors
    Ecc() : original(0), copy1(0), copy2(0) {}
    Ecc(const T& data) : original(data), copy1(data), copy2(data) { correctError();} 
    Ecc(const Ecc<T>& other) : original(other.original), copy1(other.copy1), copy2(other.copy2) { correctError(); }

    // operators
    Ecc<T>& operator=(const T& data);
    Ecc<T>& operator=(const Ecc<T>& other);
    operator T();

private:
    T volatile original;
    T volatile copy1;
    T volatile copy2;

    void correctError();

public: //for Unit Test
    void addNoiseToOriginal(const T& data) { original = data; }
    void addNoiseToCopy1(const T& data) { copy1 = data; }
    void addNoiseToCopy2(const T& data) { copy2 = data; }
};

template <typename T>
class Ecc<T*>
{
public:
    // constructors
    Ecc() : original(0), copy1(0), copy2(0) {}
    Ecc(T* const plainAddress) : original(plainAddress), copy1(plainAddress), copy2(plainAddress) { correctError(); }
    Ecc(const Ecc<T*>& other) : original(other.original), copy1(other.copy1), copy2(other.copy2) { correctError(); }

    // operators
    Ecc<T*>& operator=(T* const plainAddress)
    {
        original = copy1 = copy2 = plainAddress;
        correctError();
        return *this;
    }

    Ecc<T*>& operator=(const Ecc<T*>& other)
    {
        original = other.original;
        copy1 = other.copy1;
        copy2 = other.copy2;
        correctError();
        return *this;
    }

    operator T*()
    {
        correctError();
        return original;
    }

    T& operator*()
    {
        correctError();
        return *original; 
    }

    T* operator->()
    {
        correctError();
        return original;
    }

private:
    T* volatile original;
    T* volatile copy1;
    T* volatile copy2;

    void correctError()
    {
        if (original != copy1)
        {
            if (original == copy2)
            {
                copy1 = original;
            }
            else if (copy1 == copy2)
            {
                original = copy1;
            }
            else
            {
                /* can't correct */
            }
        }
        else if (original != copy2)
        {
            copy2 = original;
        }
        else
        {
            /* no need to correct */
        }
    }

public: //for Unit Test
    void addNoiseToOriginal(T* const data) { original = data; }
    void addNoiseToCopy1(T* const data) { copy1 = data; }
    void addNoiseToCopy2(T* const data) { copy2 = data; }
};

#endif /* ECC_HPP_ */
