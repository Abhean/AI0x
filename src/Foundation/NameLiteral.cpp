/*
 * NameStatic.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: kique
 */

#include "Logger/Logger.h"
#include "NameManager.h"
#include "NameLiteral.h"

namespace Foundation
{
#ifndef NAME_COMPILE_TIME_HASH
///
CNameLiteral::CNameLiteral(char const* _pszName) :
	CName(_pszName),
	m_pszName(_pszName)
{
	CNameManager::RegisterLiteral(*this);
}

///
CNameLiteral::~CNameLiteral()
{
	assert(!m_ListHook.is_linked());
}

#endif // NAME_COMPILE_TIME_HASH

///
CNameLiteral::CNameLiteral(CNameLiteral&& _oNameLiteral) noexcept :
	CName(std::forward<CNameLiteral>(_oNameLiteral)),
	m_pszName(_oNameLiteral.GetString())
{
#ifndef NAME_COMPILE_TIME_HASH
	m_ListHook.swap_nodes(_oNameLiteral.m_ListHook);
#endif
}

///
std::ostream& operator<<(std::ostream& _oOutStream_, CNameLiteral const& _Name)
{
	_oOutStream_ << _Name.m_pszName;
	_oOutStream_ << "#" << std::hex << _Name.GetHash();

	return _oOutStream_;
}


} // namespace Foundation 
