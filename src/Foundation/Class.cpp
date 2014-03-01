/*
 * Class.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: kique
 */

#include "Class.h"

IMPLEMENT_DYNAMIC_TYPE(Foundation::CClass, Foundation::CType)

namespace Foundation
{

///
CClass::CClass(CNameLiteral&& _oName, unsigned _uSize, TCreateInstance const& _fnCreateInstance, CNameLiteral&& _oSupertypeName, TPopulate const& _fnPopulate) :
  CType(std::forward<CNameLiteral>(_oName), _uSize, std::forward<CNameLiteral>(_oSupertypeName), _fnCreateInstance),
	m_fnPopulate(_fnPopulate)
{
	// ...
}

///
CClass::~CClass()
{
}

///
CVariable const* CClass::GetVariable(CName const& _Name) const
{
	CVariable const* pVariable = nullptr;

	auto ItVariable  = m_mapVariables.find(_Name);
	if  (ItVariable != m_mapVariables.end())
	{
		pVariable = ItVariable->second.get();
	}

	return pVariable;
}

///
void CClass::Populate ( CTypeRegistry const* _pTypeRegistry )
{
    Base::Populate ( _pTypeRegistry );

    if ( m_fnPopulate != nullptr ) 
    {
        m_fnPopulate ( this );
    }
}

///
void CClass::AddVariable ( CName const& _Name, CType const& _oType, unsigned int _uOffset )
{
  m_mapVariables[_Name].reset ( new CVariable ( _Name, _oType, _uOffset ) );
}


} // namespace Foundation
