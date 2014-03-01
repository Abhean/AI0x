/*
 * PoolManager.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: kique
 */

#include "PoolManager.h"
#include "Logger/Logger.h"

namespace Foundation
{

CPoolManager::CPoolManager()
{
	// TODO Auto-generated constructor stub

}

CPoolManager::~CPoolManager()
{
	DestroyAllPools();
}

///
IObjectPool* CPoolManager::GetPool(CName const& _Name)
{
	IObjectPool* pPool = nullptr;

	TPoolMapIt ItPool = m_mapPool.find(_Name);
	if (ItPool != m_mapPool.end())
	{
		pPool = ItPool->second;
	}
	else
	{
		Logger::Log(Logger::ELevel::WARNING, "CPoolManager::GetPool: Pool '%' does not exist", _Name);
	}

	return pPool;
}

///
void CPoolManager::DestroyAllPools()
{
	for (auto oPool: m_mapPool)
	{
		delete oPool.second;
	}

	m_mapPool.clear();
}

} /* namespace Foundation */
