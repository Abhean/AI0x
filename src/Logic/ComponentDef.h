/*
 *
 */

#ifndef LOGIC_COMPONENTDEF_H
#define LOGIC_COMPONENTDEF_H

#include "Foundation/Object.h"
#include "Foundation/Types.h"
#include "Foundation/Pointer.h"
#include "rapidxml.hpp"
#include <cstdlib>
#include <memory>

namespace Logic
{

struct SAux
{
  SAux() :
   fVar {0.0},
   sVar {}
   { /* ... */ }
  
  float fVar;
  std::string sVar;
};

typedef std::unique_ptr<SAux> TSAuxUniquePtr;

class CComponentDef : public Foundation::CObject
{
  DECLARE_CLASS(CComponentDef, Foundation::CObject)

public:
  
  CComponentDef() : m_pAux2(nullptr)
  { /* ... */ }
  
  static void Populate(Foundation::CClass* _pClass_);

public:
  
  Foundation::CName const& GetName() const { return m_Name; }
          
private:
  
  Foundation::CName m_Name;
  SAux m_Aux;
  SAux* m_pAux2;
  TSAuxUniquePtr m_pAux3;
};

} // namespace Logic

DECLARE_CLASS_EX(Logic, SAux)
DECLARE_POINTER_TYPE(Logic, SAux)
DECLARE_POINTER_TYPE_EX(Logic, TSAuxUniquePtr)


#endif // LOGIC_COMPONENTDEF_H
