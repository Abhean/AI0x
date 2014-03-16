/*
 * Collection.h
 *
 *  Created on: 03/11/2012
 *      Author: kique
 */

#ifndef FOUNDATION_COLLECTION_H_
#define FOUNDATION_COLLECTION_H_

#include "Type.h"

namespace Foundation
{

class CCollection : public CType 
{
  DECLARE_DYNAMIC_TYPE(CCollection)

public:
  
  typedef std::function<void (void* pCollection_, void const* _pElement)> TAddElement;
  
  
  template <typename T>
  CCollection(T* _pTypeDummy, CName const& _Name, TCreateInstance const& _fnCreateInstance) :
    CType(_pTypeDummy, _Name, _fnCreateInstance),
    m_fnAddElement(nullptr)
  {
    // ...
  }

  virtual ~CCollection();
   
private:
  
  TAddElement m_fnAddElement;      
};

} /* namespace Foundation */
#endif /* FOUNDATION_COLLECTION_H_ */
