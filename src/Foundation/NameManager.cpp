/*
 * NameManager.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: kique
 */

#include "NameManager.h"
#include "Logger/Logger.h"

namespace Foundation
{

///
CNameManager::CNameManager()
{
#ifndef NAME_COMPILE_TIME_HASH
	// Create Types
	for (auto& oNameLiteral: GetStaticLiteralList())
	{
		StringTableInsert(oNameLiteral.GetHash(), oNameLiteral.GetString());
	}

	GetStaticLiteralList().clear();
#endif // NAME_COMPILE_TIME_HASH
}

///
CNameManager::~CNameManager()
{
}

#ifndef NAME_COMPILE_TIME_HASH
///
void CNameManager::RegisterLiteral(CNameLiteral& _oNameLiteral_)
{
	if (CNameManager::IsInitialized())
	{
		CNameManager::GetInstance()->StringTableInsert(_oNameLiteral_.GetHash(), _oNameLiteral_.GetString());
	}
	else
	{
		StaticLiteralListInsert(_oNameLiteral_);
	}
}

///
void CNameManager::StaticLiteralListInsert(CNameLiteral& _oName_)
{
	assert(!CNameManager::IsInitialized());
	GetStaticLiteralList().push_back(_oName_);
}

///
// string copy
void CNameManager::StringTableInsert(unsigned _uHash, char const* _pszString)
{
	StringTableInsert(_uHash, std::string(_pszString));
}

///
// string move
void CNameManager::StringTableInsert(unsigned _uHash, std::string&& _sString)
{
	// Check collisions
	auto ItValue = m_HashToStringMap.find(_uHash);
	if  (ItValue == m_HashToStringMap.end())
	{
		m_HashToStringMap.insert({_uHash, _sString});
	}
	else
	{
		// Check collisions
		assert(ItValue->second == _sString);
	}
}

///
std::string CNameManager::StringTableGet(unsigned _uHash)
{
  std::string sString = "";
  
  auto ItValue = m_HashToStringMap.find(_uHash);
  if  (ItValue != m_HashToStringMap.end())
  {
    sString = ItValue->second;
  }
  
  return sString;
}

#endif // NAME_COMPILE_TIME_HASH

} // namespace Foundation 
