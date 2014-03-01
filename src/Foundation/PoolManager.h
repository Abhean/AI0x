/*
 * PoolManager.h
 *
 *  Created on: Apr 25, 2012
 *      Author: kique
 */

#ifndef POOLMANAGER_H_
#define POOLMANAGER_H_

#include "IObjectPool.h"
#include "ObjectCompactPool.h"
#include "Foundation/Name.h"
#include "Foundation/Type.h"
#include "Foundation/Singleton.h"
#include <map>


namespace Foundation
{
///
class CPoolManager : public CSingleton<CPoolManager>
{
public:

			 CPoolManager();
	virtual ~CPoolManager();

	template<typename T>
	bool CreatePool(unsigned _uSize)
	{
		bool bPoolOk = false;

    CType const& Type = StaticType<T>::Value();
		assert(GetPool(Type.GetName()) == nullptr);

		IObjectPool* pPool = new TPoolType<T>(_uSize);
		if (pPool != nullptr)
		{
			m_mapPool.insert(std::pair<CName, IObjectPool*>(Type.GetName(), pPool));
			bPoolOk = true;
		}

		return bPoolOk;
	}

	///
	IObjectPool::THandle CreateInstance(CName const& _TypeName)
	{
		IObjectPool::THandle hInstance = IObjectPool::INVALID_HANDLE;

		IObjectPool* pPool = GetPool(_TypeName);
		if (pPool != nullptr)
		{
			hInstance = pPool->Alloc();
		}

		return hInstance;
	}

	///
	template <typename T>
	IObjectPool::THandle CreateInstance()
	{
    CType const& Type = StaticType<T>::Value();
		return CreateInstance(Type.GetName());
	}

	///
	void DestroyInstance(CName const& _TypeName, IObjectPool::THandle _hInstance)
	{
		IObjectPool* pPool = GetPool(_TypeName);
		if (pPool != nullptr)
		{
			pPool->Free(_hInstance);
		}
	}

private:

	IObjectPool* GetPool(CName const& _Name);

	void DestroyAllPools();

	template <typename T>
	using TPoolType = CObjectCompactPool<T>;

	using TPoolMap = std::map<CName, IObjectPool*>;
	using TPoolMapIt = TPoolMap::iterator;

	TPoolMap m_mapPool;
};

} /* namespace Foundation */
#endif /* POOLMANAGER_H_ */
