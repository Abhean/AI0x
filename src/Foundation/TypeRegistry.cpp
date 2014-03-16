/*
 * TypeRegistry.cpp
 *
 *  Created on: Feb 20, 2012
 *      Author: kique
 */
#include "TypeRegistry.h"
#include "Type.h"

namespace Foundation
{
///
CTypeRegistry::CTypeRegistry()
{
  // Create Types
  for (auto& oType: GetStaticTypeList())
  {
    RegisterType(&oType, false);
  }

  // Populate Types
  // @NOTE[egarcia]: All types must be registered before this step (they will be search for)
  for (auto& oType: GetStaticTypeList())
  {
    oType.Populate(this);
  }

  GetStaticTypeList().clear();

  // Register type conversions
  for (auto& oTypeCastEntry: GetStaticTypeCastList())
  {
    CType* pType = GetTypeByName(oTypeCastEntry.nSourceType);
    assert(pType);
    
    pType->RegisterTypeCast(oTypeCastEntry.nTargetType, oTypeCastEntry.fnCast);
  }

  GetStaticTypeCastList().clear();
}

///
CTypeRegistry::~CTypeRegistry()
{
}

///
void CTypeRegistry::RegisterType(CType* _pType, bool _bOwner)
{
	assert(_pType != nullptr);
	m_TypeMap.insert(std::pair<CName, CTypeEntry>(_pType->GetName(), CTypeEntry { _pType, _bOwner }));
}

///
CType const* CTypeRegistry::GetTypeByName(CName const& _Name) const
{
    CType const* pType = nullptr;

    TTypeMapConstIt ItType = m_TypeMap.find(_Name);
    if (ItType != m_TypeMap.end())
    {
      pType = ItType->second.GetType();
    }

    return pType;
}

///
CType* CTypeRegistry::GetTypeByName(CName const& _Name)
{
    CType* pType = nullptr;

    TTypeMapIt ItType = m_TypeMap.find(_Name);
    if (ItType != m_TypeMap.end())
    {
      pType = ItType->second.GetType();
    }

    return pType;  
}

///
void CTypeRegistry::StaticTypeListAdd(CType& _oType_)
{
  GetStaticTypeList().push_back(_oType_);
}


///
void  CTypeRegistry::StaticTypeCastListAdd(STypeCastStaticListEntry& _oTypeCastEntry_)
{
  GetStaticTypeCastList().push_back(_oTypeCastEntry_);
}

} // namespace Foundation
