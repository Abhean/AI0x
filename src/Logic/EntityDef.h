/*
 *
 */

#ifndef LOGIC_ENTITYDEF_H
#define LOGIC_ENTITYDEF_H

#include "Foundation/Object.h"
#include "Foundation/Name.h"
#include <unordered_map>

namespace Logic
{
  
// Forward declarations
class CComponentDef;

class CEntityDef : public Foundation::CObject
{
  DECLARE_CLASS(CEntityDef, Foundation::CObject)
  
public:
  
  CEntityDef();
  CEntityDef(CEntityDef const& other);
  ~CEntityDef();
  CEntityDef& operator=(CEntityDef const& other);
  bool operator==(CEntityDef const& other);
    
private:
  
  //using TComponentMap = std::unordered_map<Foundation::CName, Foundation::RelocatablePtr<CComponentDef const>>;
  using TComponentMap = std::unordered_map<Foundation::CName, CComponentDef const*>;
  
  Foundation::CName m_nName;
  TComponentMap m_mapComponents;
};

} // Logic

#endif // LOGIC_ENTITYDEF_H
