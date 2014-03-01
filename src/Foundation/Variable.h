/*
 * Variable.h
 *
 *  Created on: Oct 21, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_VARIABLE_H_
#define FOUNDATION_VARIABLE_H_

#include "Field.h"
#include "Types.h"

namespace Foundation
{
  class CType;
  class CObject;
}

namespace Foundation
{

class CVariable : public CField
{
public:
  
  CVariable(CName _Name, CType const& _Type, unsigned _uOffset);
  virtual ~CVariable();

  //inline bool IsPointer() const { return m_bIsPointer; }

  ///
  template <typename T>
  bool GetValue(void const* _pObject, T* pValue_) const;

   ///
  template <typename T>
  bool SetValue(void* pObject_, T _Value) const;

  ///
  void const* GetValuePtr(void const* _pObject) const { return reinterpret_cast<void const*>(reinterpret_cast<char const*>(_pObject) + m_uOffset); }
  
  ///
  void* GetValuePtr(void* _pObject) const { return reinterpret_cast<void*>(reinterpret_cast<char*>(_pObject) + m_uOffset); }
  
  ///
  CType const& GetType() const { return m_Type; }

private:
  
  CType const& m_Type;
  unsigned     m_uOffset;
};

//--------------------------------------------------------
// Template implementation
//--------------------------------------------------------

///
template <typename T>
bool CVariable::GetValue(void const* _pObject, T* pValue_) const
{
  return m_Type.GetValue<T>(GetValuePtr(_pObject), pValue_);
}

///
template <typename T>
bool CVariable::SetValue(void* pObject_, T _Value) const
{
  return m_Type.SetValue<T>(GetValuePtr(pObject_), _Value);
}

} /* namespace Foundation */
#endif /* FOUNDATION_VARIABLE_H_ */
