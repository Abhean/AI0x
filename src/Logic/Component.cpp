/*
 * Component.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: kique
 */

#include <cstddef>
#include "Component.h"
#include "Foundation/Types.h"
#include "Foundation/Class.h"

IMPLEMENT_CLASS(Logic::CComponent, Foundation::CTypedObject);

using Foundation::operator "" _n;

namespace Logic
{
  
CComponent::CComponent() :
  m_pComponentDef(nullptr)
{
  // TODO Auto-generated constructor stub
  
}

CComponent::~CComponent()
{
	// TODO Auto-generated destructor stub
}

///
void CComponent::Populate(Foundation::CClass* _pClass_)
{
  //_pClass_->AddVariable<CComponentDef*>("m_pComponentDef"_n, offsetof(CComponent, m_pComponentDef));
  //_pClass_->AddVariable<Foundation::CName>("m_Name"_n, offsetof(CComponent, m_Name));
  //_pClass_->AddVariable<int>("m_iTest"_n, offsetof(CComponent, m_iTest));
}

} // namespace Logic
