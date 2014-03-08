/*
 *
 */

#include "ComponentDef.h"
#include "Serialization/DataStreamXML.h"

using Foundation::operator "" _n;

IMPLEMENT_CLASS(Logic::CComponentDef, Foundation::CObject);
IMPLEMENT_CLASS_EX(Logic, SAux, , 
// CreateInstance                   
[]() { return new Logic::SAux(); },
// Populate
[](Foundation::CClass* _pClass_) 
{
  _pClass_->AddVariable<float>("fVar"_n, offsetof(SAux, fVar));
  _pClass_->AddVariable<std::string>("sVar"_n, offsetof(SAux, sVar));
});

IMPLEMENT_POINTER_TYPE(Logic, SAux);
IMPLEMENT_TYPE_CAST_NSPT_PT(Logic, SAux, void);
IMPLEMENT_TYPE_CAST_PT_NSPT(void, Logic, SAux);

IMPLEMENT_POINTER_TYPE_EX(Logic, TSAuxUniquePtr, Logic, SAux);

namespace Foundation
{
  template <>
  struct TypeCast<Logic::TSAuxUniquePtr, void*>
  {
    static bool Apply(void const* _pSource, void* pTarget_)
    {
      *(static_cast<void**>(pTarget_)) = static_cast<Logic::TSAuxUniquePtr const*>(_pSource)->get();
      return true;
    }
  };
  
  template <>
  struct TypeCast<void*, Logic::TSAuxUniquePtr>
  {
    static bool Apply(void const* _pSource, void* pTarget_)
    {
      static_cast<Logic::TSAuxUniquePtr*>(pTarget_)->reset(*static_cast<Logic::SAux* const*>(_pSource));
      return true;
    }
  };
}

IMPLEMENT_TYPE_CAST_NST_PT(Logic, TSAuxUniquePtr, void);
IMPLEMENT_TYPE_CAST_PT_NST(void, Logic, TSAuxUniquePtr);
// @TODO[egarcia]: Casts

namespace Logic
{

///
void CComponentDef::Populate(Foundation::CClass* _pClass_)
{
  _pClass_->AddVariable<Foundation::CName>("m_Name"_n, offsetof(CComponentDef, m_Name));
  _pClass_->AddVariable<Logic::SAux>("m_Aux"_n, offsetof(CComponentDef, m_Aux));
  _pClass_->AddVariable<Logic::SAux*>("m_pAux2"_n, offsetof(CComponentDef, m_pAux2));
  _pClass_->AddVariable<Logic::TSAuxUniquePtr>("m_pAux3"_n, offsetof(CComponentDef, m_pAux3));
}

} // namespace Logic

