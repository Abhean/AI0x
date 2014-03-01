/*
 * Pool.h
 *
 *  Created on: Sep 23, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_POOL_H_
#define FOUNDATION_POOL_H_


#include <cassert>
#include <vector>
#include <boost/optional.hpp>

namespace Foundation
{

template <typename T>
class CPool
{
public:

	// Types
	typedef unsigned int THandle;
	constexpr static THandle INVALID_HANDLE = -1;

	// Initialization / Destruction
	CPool(size_t _uSize) :
		m_uNumAllocatedElems(0),
		m_vectElemsGenerations(_uSize),
		m_vectElemsAllocated(_uSize),
		m_vectElems(_uSize)
	{
		//...
	}

	virtual ~CPool()
	{

	}

	// Management
	T*     GetData    () const { return m_vectElems.data(); }
	size_t GetNumAllocatedElems() const { return m_uNumAllocatedElems; }

	///
	T* GetInstancePtr(THandle _hInstance)
	{
		T* pInstance = nullptr;

		unsigned short uGeneration = GetHandleGeneration(_hInstance);
		unsigned short uIndex = GetHandleElemIndex(_hInstance);

		if (m_vectElemsGenerations[uIndex] == uGeneration)
		{
			pInstance = m_vectElems[uIndex];
		}

		return pInstance;
	}

	///
	THandle Alloc()
	{
		THandle hInstance = INVALID_HANDLE;

		if (m_uNumAllocatedElems <  m_vectElems.size())
		{
			boost::optional<unsigned short> oiFreeElemIdx = FindFreeElemIdx();

			if (oiFreeElemIdx)
			{
				++m_uNumAllocatedElems;
				hInstance = oiFreeElemIdx.get() + (m_vectElemsGenerations[oiFreeElemIdx.get()] << 16);

				// @TODO[egarcia]: Init elem
			}
		}

		return hInstance;
	}

	///
	void Free(THandle _hInstance)
	{
		assert(m_uNumAllocatedElems > 0);

		// @TODO[egarcia]: Deinit elem


		// Free pool element
		unsigned short uFreeElemIndex = GetHandleElemIndex(_hInstance);
		assert((uFreeElemIndex < m_vectElems.size()) && GetHandleGeneration(_hInstance) == m_vectElemsGenerations[uFreeElemIndex]);

		m_vectElemsAllocated[uFreeElemIndex] = false;
		--m_uNumAllocatedElems;

		// Inc handle generation
		IncHandleGeneration(uFreeElemIndex);
	}

private:

	// Types
	typedef std::vector<T>               	TElemVector;
	typedef std::vector<unsigned short>	TElemGenerationVector;
	typedef std::vector<bool>				TElemAllocatedVector;

	//
	boost::optional<unsigned short> FindFreeElemIdx()
	{
		boost::optional<unsigned short> ouFreeElemIdx;

		for (unsigned short uElemIdx = 0; uElemIdx < m_vectElems.size(); ++uElemIdx)
		{
			if (m_vectElemsAllocated[uElemIdx])
			{
				ouFreeElemIdx.reset(uElemIdx);
				break;
			}
		}

		return ouFreeElemIdx;
	}

	//
	unsigned short GetHandleElemIndex (THandle _hHandle)
	{
		return static_cast<unsigned>(_hHandle) & 0xFFFF;
	}

	//
	unsigned short GetHandleGeneration (THandle _hHandle)
	{
		return static_cast<unsigned>(_hHandle) >> 16;
	}

	//
	void IncHandleGeneration(unsigned short _uIndex)
	{
		++m_vectElemsGenerations[_uIndex];
	}

	//
	size_t 					m_uNumAllocatedElems;
	TElemAllocatedVector	m_vectElemsAllocated;
	TElemVector   			m_vectElems;

	TElemGenerationVector	m_vectElemsGenerations;
};


} // Foundation

#endif /* FOUNDATION_POOL_H_ */
