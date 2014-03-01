/*
 * 
 */

#ifndef BITFLOW_AGENTCOMPONENTDEF_H
#define BITFLOW_AGENTCOMPONENTDEF_H

#include "Logic/ComponentDef.h"

namespace Bitflow
{
 
///
class CAgentComponentDef : public Logic::CComponentDef
{
  DECLARE_CLASS(CAgentComponentDef, Logic::CComponentDef)
  
public:
  
  static void Populate(Foundation::CClass* _pClass_);
  
private:
  
};
  
} // namespace Bitflow

#endif // BITFLOW_AGENTCOMPONENTDEF_H
