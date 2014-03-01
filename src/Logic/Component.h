/*
 * Component.h
 *
 *  Created on: Sep 26, 2011
 *      Author: kique
 */

#ifndef LOGIC_COMPONENT_H_
#define LOGIC_COMPONENT_H_

#include "Foundation/Object.h"
#include "Foundation/Name.h"

namespace Logic
{
  
// Forward declarations
class CComponentDef;  
  
///  
class CComponent : public Foundation::CObject
{
  DECLARE_CLASS(CComponent, Foundation::CObject)

public:
  
  CComponent();
  virtual ~CComponent();

  static void Populate(Foundation::CClass* _pClass_);

  CComponentDef const* GetComponentDef() const { return m_pComponentDef; }
        
private:

  CComponentDef const* m_pComponentDef;
};


} // namespace Logic

#endif /* LOGIC_COMPONENT_H_ */
