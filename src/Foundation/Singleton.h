/*
 * Singleton.h
 *
 *  Created on: Sep 26, 2011
 *      Author: kique
 */

#ifndef FOUNDATION_SINGLETON_H_
#define FOUNDATION_SINGLETON_H_

#include <cassert>
#include <iostream>

namespace Foundation
{

template <typename T>
class CSingleton
{
public:

	static bool IsInitialized()
	{
		return m_pInstance != nullptr;
	}

	static void Init()
	{
		assert(m_pInstance == 0);
		m_pInstance = new T();
	}

	static void Done()
	{
		assert(m_pInstance != 0);
		delete m_pInstance;
		m_pInstance = 0;
	}

	static T* GetInstance()
	{
		assert(m_pInstance != 0);
		return m_pInstance;
	}

protected:

			 CSingleton() { /* ... */ }
	virtual ~CSingleton() { /* ... */ }

	// @TODO[egarcia]: virtual initialization / finalization methods

	static T* m_pInstance;
};

template <typename T>
T* CSingleton<T>::m_pInstance = 0;


} // Foundation

#endif // FOUNDATION_SINGLETON_H_
