/*
 * CompactPool.h
 *
 *  Created on: Feb 27, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_COMPACTPOOL_H_
#define FOUNDATION_COMPACTPOOL_H_

#include <cassert>
#include <vector>
#include <stddef.h>
#include "Pool.h"
#include "IObjectPool.h"

namespace Foundation
{

// @TODO[egarcia]: Sync compacting
template <typename T>
class CObjectCompactPool : public IObjectPool
{
public:

	static unsigned short const INVALID_INDEX = 0xFFFF;

	// Initialization / Destruction

	///
	CObjectCompactPool(size_t _uSize) :
		m_uNumElems(_uSize),
		m_uNumAllocatedElems(0),
		m_uLockCount(0)
	{
		m_pElems = new T[_uSize];
		assert(m_pElems != nullptr);

		m_pHandleData = new SHandleData[_uSize];
		assert(m_pHandleData != nullptr);
	}

	///
	virtual ~CObjectCompactPool()
	{
		delete[] m_pElems;
	}

	// Management
	T*     GetData    () const { return m_pElems; }
	size_t GetDataSize() const { return m_uNumAllocatedElems * sizeof(T); }

	size_t GetNumAllocatedElems() const { return m_uNumAllocatedElems; }


	///
	virtual THandle	 Alloc() override
	{
		assert(!IsLocked());

		THandle hInstance = INVALID_HANDLE;

		if (m_uNumAllocatedElems < m_uNumElems)
		{
			unsigned short uHandleIdx = GetFreeHandleIndex();
			SHandleData& oHandleData = m_pHandleData[uHandleIdx];

			oHandleData.uElemIndex = m_uNumAllocatedElems++;
			hInstance = oHandleData.uElemIndex + (oHandleData.uGeneration << 16);

			++m_uNumAllocatedElems;

			// @TODO[egarcia]: Init m_pElems[oHandleData.uElemIdx]
		}

		return hInstance;
	}

	///
	virtual void Free(THandle _hInstance) override
	{
		assert(!IsLocked());
		assert(m_uNumAllocatedElems > 0);

		unsigned short uHandleIndex = GetHandleIndex(_hInstance);
		assert(uHandleIndex < m_uNumElems);

		SHandleData& oHandleData = m_pHandleData[uHandleIndex];
		if (oHandleData.uGeneration == GetHandleGeneration(_hInstance))
		{
			// @TODO[egarcia]: Deinit m_pElems[oHandleData.uElemIdx]

			// Compact Pool
			unsigned uLastAllocatedElemIndex = m_uNumAllocatedElems - 1;
			if (oHandleData.uElemIndex < uLastAllocatedElemIndex)
			{
				m_pElems[oHandleData.uElemIndex] = std::move(m_pElems[uLastAllocatedElemIndex]);
			}

			--m_uNumAllocatedElems;

			oHandleData.Free();
		}
	}

	/// @TODO[egarcia]: Wrapper "smart pointer" / iterator
	virtual CObject* Lock (THandle _hInstance) override
	{
		assert(m_uLockCount < 0xFFFFFFFF);

		CObject* pObject = nullptr;

		unsigned short uHandleIndex = GetHandleIndex(_hInstance);
		assert(uHandleIndex < m_uNumElems);

		const SHandleData& oHandleData = m_pHandleData[uHandleIndex];
		if (oHandleData.uGeneration == GetHandleGeneration(_hInstance))
		{
			pObject = &m_pElems[oHandleData.uElemIndex];
			++m_uLockCount;
		}

		return pObject;
	}

	///
	virtual void Unlock (THandle _hInstance) override
	{
		assert(m_uLockCount > 0);

		// ...
		--m_uLockCount;
	}

	///
	virtual bool IsLocked() const override { return m_uLockCount > 0; }

private:

	// Types
	struct SHandleData
	{
		SHandleData() :
			uElemIndex(INVALID_INDEX),
			uGeneration(0)
		{ /*  ... */ }

		void Free() { uElemIndex = INVALID_INDEX; ++uGeneration; }
		bool IsFree() const { return uElemIndex == INVALID_INDEX; }

		unsigned short uElemIndex;
		unsigned short uGeneration;
	};

	// Methods
	SHandleData& GetHandleData(THandle _uHandle)
	{
		return m_pHandleData[GetHandleIndex(_uHandle)];
	}

	///
	unsigned short GetFreeHandleIndex()
	{
		unsigned short uFreeHandleDataIdx = INVALID_INDEX;

		for (unsigned uHandleIdx = 0; uHandleIdx < m_uNumElems; ++uHandleIdx)
		{
			const SHandleData& oHandleData = m_pHandleData[uHandleIdx];
			if (oHandleData.IsFree())
			{
				uFreeHandleDataIdx = uHandleIdx;
				break;
			}
		}

		return uFreeHandleDataIdx;
	}

	//
	unsigned short GetHandleIndex (THandle _hHandle)
	{
		return static_cast<unsigned>(_hHandle) & 0xFFFF;
	}

	//
	unsigned short GetHandleGeneration (THandle _hHandle)
	{
		return static_cast<unsigned>(_hHandle) >> 16;
	}


	// Variables
	T*   	 			 m_pElems;
	SHandleData* 	 	 m_pHandleData;
	unsigned short		 m_uNumElems;
	unsigned short     m_uNumAllocatedElems;
	unsigned 			 m_uLockCount;
};


} // Foundation

#endif /* FOUNDATION_COMPACTPOOL_H_ */
