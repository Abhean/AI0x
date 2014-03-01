/*
 *
 */

#include "EntityDef.h"

IMPLEMENT_CLASS(Logic::CEntityDef, Foundation::CTypedObject);

namespace Logic
{

CEntityDef::CEntityDef()
{

}

CEntityDef::CEntityDef(const CEntityDef& other)
{

}

CEntityDef::~CEntityDef()
{

}

CEntityDef& CEntityDef::operator=(const CEntityDef& other)
{
  if (this != &other)
  {
  }
  
  return *this;
}

bool CEntityDef::operator==(const CEntityDef& other)
{
  return false;
}

} // namespace Logic