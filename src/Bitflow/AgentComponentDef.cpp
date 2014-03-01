/*
 * 
 */

#include "AgentComponentDef.h"

IMPLEMENT_CLASS(Bitflow::CAgentComponentDef, Logic::CComponentDef);

using Foundation::operator "" _n;

namespace Bitflow
{

///
void CAgentComponentDef::Populate(Foundation::CClass* _pClass_)
{
  Super::Populate(_pClass_);
 
  //_pClass_->AddVariable<int>("m_iTest"_n, offsetof(CComponent, m_iTest));
}
  
} // namespace Bitflow