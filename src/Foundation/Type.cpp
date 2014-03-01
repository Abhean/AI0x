/*
 * Type.cpp
 *
 *  Created on: Nov 22, 2012
 *      Author: kique
 */
#include "Type.h"
#include "TypeRegistry.h"
#include "Logger/Logger.h"

IMPLEMENT_DYNAMIC_TYPE(Foundation::CType, )

namespace Foundation
{

///
CType::~CType()
{
	/* ... */
}

///
CType::CType(CNameLiteral&& _oName, unsigned _uSize, CNameLiteral&& _oSupertypeName, TCreateInstance const& _fnCreateInstance) :
	m_oName(std::forward<CNameLiteral>(_oName)),
	m_uSize(_uSize),
	m_oSupertypeName(std::forward<CNameLiteral>(_oSupertypeName)),
	m_fnCreateInstance(_fnCreateInstance)
{
	// Add Type to static list
	CTypeRegistry::StaticTypeListAdd(*this);
}

///
void* CType::CreateInstance() const
{
	return (m_fnCreateInstance != nullptr) ? m_fnCreateInstance() : nullptr;
}

///
void CType::Populate(const CTypeRegistry* _pTypeRegistry)
{
  if ( !m_oSupertypeName.IsEmpty() ) 
  {
    assert ( m_pSupertype == nullptr );
    
    m_pSupertype = CType::DynamicCast<CType const> ( _pTypeRegistry->GetTypeByName ( m_oSupertypeName ) );
    if ( m_pSupertype == nullptr ) 
    {
      Logger::Log ( Logger::ELevel::ERROR, "CType::Populate, Supertype not found or it is not a class [%]", m_oSupertypeName );
    }
  }
} 

///
bool CType::IsKindOf(CType const& _Type) const
{
  return (*this == _Type) || ((m_pSupertype != nullptr) && (m_pSupertype->IsKindOf(_Type)));
}


///
TTypeCast CType::GetTypeCast(CName const& _nTarget) const
{
  TTypeCast fnCast = nullptr;
  
  TTypeCastMapConstIt ItCast = m_TypeCastMap.find(_nTarget);
  if (ItCast != m_TypeCastMap.end())
  {
    fnCast = ItCast->second;
  }
  
  return fnCast;
}


///
void CType::RegisterTypeCast(CName const& _nTarget, TTypeCast const& _fnCast)
{
  m_TypeCastMap[_nTarget] = _fnCast;
}

} // namespace Foundation



