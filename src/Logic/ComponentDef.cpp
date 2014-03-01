/*
 *
 */

#include "ComponentDef.h"
#include "Serialization/DataStreamXML.h"

using Foundation::operator "" _n;

IMPLEMENT_POINTER_TYPE(Logic, SAux);
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

namespace Logic
{

///
void CComponentDef::Populate(Foundation::CClass* _pClass_)
{
  _pClass_->AddVariable<Foundation::CName>("m_Name"_n, offsetof(CComponentDef, m_Name));
  _pClass_->AddVariable<Logic::SAux>("m_Aux"_n, offsetof(CComponentDef, m_Aux));
  _pClass_->AddVariable<Logic::SAux*>("m_pAux2"_n, offsetof(CComponentDef, m_pAux2));
}

} // namespace Logic

// @TODO[egarcia]: Remove.
// namespace Foundation
// {
//   //----------------------------------------------
//   template <>
//   inline bool TypeCast<Serialization::xml_node_char*, Logic::SAux>(void const* _pSource, void* pTarget_)
//   {  
//     rapidxml::xml_node<>* const pxmlNode = *static_cast<rapidxml::xml_node<>* const*>(_pSource);
//     Logic::SAux* pAux = static_cast<Logic::SAux*>(pTarget_);
//     
//     auto pxmlAttribute = pxmlNode->first_attribute();
//     pxmlAttribute = pxmlAttribute->next_attribute();
//     pAux->fVar = ::atof(pxmlAttribute->value());
//     pxmlAttribute = pxmlAttribute->next_attribute();
//     pAux->sVar = std::string { pxmlAttribute->value() };
//   } 
// }
// 
// IMPLEMENT_TYPE_CAST_NSPT_NST(Serialization, xml_node_char, Logic, SAux);
