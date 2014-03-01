/*
 * Name.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: kique
 */

#include "NameManager.h"
#include "Name.h"

namespace Foundation
{

///
// @TODO[egarcia]: Review argument passing / move
CName::CName(std::string&& _sName) noexcept :
#ifdef NAME_COMPILE_TIME_HASH
	m_uName(COMPILE_TIME_CRC32_STR(_sName.c_str()))
{ /* ... */}
#else
	m_uName(rt_crc32(_sName.c_str()))
{
	if (CNameManager::IsInitialized())
	{
		CNameManager::GetInstance()->StringTableInsert(m_uName, std::move(_sName));
	}
}
#endif // NAME_COMPILE_TIME_HASH

///
CName::CName(std::string const& _sName) :
		CName(_sName.c_str())
{ /* ... */ }

#ifndef NAME_COMPILE_TIME_HASH
///
CName::CName(char const* _pszName) :
	m_uName(rt_crc32(_pszName))
{
  if (CNameManager::IsInitialized())
  {
          CNameManager::GetInstance()->StringTableInsert(m_uName, _pszName);
  }
}
#endif // NAME_COMPILE_TIME_HASH

///
std::ostream& operator<<(std::ostream& _oOutStream_, CName const& _Name)
{
#ifndef NAME_COMPILE_TIME_HASH
  _oOutStream_ << CNameManager::GetInstance()->StringTableGet(_Name.m_uName);
#endif
  _oOutStream_ << "#" << std::hex << _Name.m_uName;
  return _oOutStream_;
}

} // namespace Foundation


