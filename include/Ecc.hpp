/*
 * Ecc.hpp
 *
 *  Created on: 2019/07/25
 *      Author: 010880016
 */

#ifndef ECC_HPP_
#define ECC_HPP_

// #include <iostream>

template <typename T> // T must be bool, pointer or a kind of Integer type
class EccBase
{
public:
	// constructors
	EccBase() : original(0), copy1(0), copy2(0) { /* std::cout << "default constructor" << std::endl; */ }
	EccBase(const T& data) : original(data), copy1(data), copy2(data) { correctError(); /* std::cout << "constructor with arg" << std::endl; */ }
	EccBase(const EccBase<T>& other) : original(other.original), copy1(other.copy1), copy2(other.copy2) { correctError(); /* std::cout << "copy constructor" << std::endl; */ }

	// operators
	EccBase<T>& operator=(const T& data) { original = copy1 = copy2 = data; correctError(); /* std::cout << "assignment operator" << std::endl; */ return *this; }
	EccBase<T>& operator=(const EccBase<T>& other)  { original = other.original, copy1 = other.copy1; copy2 = other.copy2; correctError(); /* std::cout << "copy assignment" << std::endl; */ return *this; }
	operator T() { correctError(); return original; }

protected:
	T volatile original;
	T volatile copy1;
	T volatile copy2;

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
	void addNoiseToOriginal(const T& data) { original = data; }
	void addNoiseToCopy1(const T& data) { copy1 = data; }
	void addNoiseToCopy2(const T& data) { copy2 = data; }
};

template <typename T> // T must be bool or a kind of Integer type
class Ecc : public EccBase<T>
{
public:
	// constructors
	Ecc() : EccBase<T>() {}
	Ecc(const T& plainData) : EccBase<T>(plainData) {}
	Ecc(const Ecc<T>& other) : EccBase<T>(other) {}

	// operators
	Ecc<T>& operator=(const T& data) { return static_cast<Ecc<T>&>(EccBase<T>::operator=(data)); }
	Ecc<T>& operator=(const Ecc<T>& other) { return static_cast<Ecc<T>&>(EccBase<T>::operator=(other));}
};

template <typename T>
class Ecc<T*> : public EccBase<T*>
{
public:
	// constructors
	Ecc() : EccBase<T*>() {}
	Ecc(T* const plainAddress) : EccBase<T*>(plainAddress) {}
	Ecc(const Ecc<T*>& other) : EccBase<T*>(other) {}

	// operators
	Ecc<T*>& operator=(T* const plainAddress) { return static_cast<Ecc<T*>&>(EccBase<T*>::operator=(plainAddress)); }
	Ecc<T*>& operator=(const Ecc<T*>& other) { return static_cast<Ecc<T*>&>(EccBase<T*>::operator=(other));}

	T& operator*() { EccBase<T*>::correctError(); return *EccBase<T*>::original; }
	T* operator->() { EccBase<T*>::correctError(); return EccBase<T*>::original; }
};

#endif /* ECC_HPP_ */
