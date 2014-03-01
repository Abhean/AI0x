/*
 * Object.h
 *
 *  Created on: Feb 19, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_OBJECT_H_
#define FOUNDATION_OBJECT_H_

#include "Class.h"

namespace Foundation
{
  
class CObject
{
public:

	// Types

	// Initialization / Destruction
	virtual ~CObject() { /* ... */ }

	// Type Management
	virtual CClass const& GetClass() const = 0;

	///
	template <typename T>
	bool GetValue(CName const& _VariableName, T* pValue_) const
	{
		assert(pValue_ != nullptr);

		bool bOk = false;

		CVariable const* pVariable = GetClass().GetVariable(_VariableName);
		if (pVariable != nullptr)
		{
			bOk = pVariable->GetValue(this, pValue_);
		}

		return bOk;
	}
	
	///
	template <typename T>
	bool SetValue(CName const& _VariableName, T _Value)
  {
    bool bOk = false;
    
    CVariable const* pVariable = GetClass().GetVariable(_VariableName);
    if (pVariable != nullptr)
    {
      bOk = pVariable->SetValue(this, _Value);
    }
    
    return bOk;
  }
  
	///
	template <typename T>
	bool GetValuePtr(CName const& _VariableName, T const** ppValue_) const
	{
		assert(ppValue_ != nullptr);

		bool bOk = false;

		CVariable const* pVariable = GetClass().GetVariable(_VariableName);
		if (pVariable != nullptr)
		{
      if (pVariable->GetType().IsKindOf(StaticType<T>::Value()))
      {
        *ppValue_ = static_cast<T const*>(pVariable->GetValuePtr(this));
      }
      else
      {
        Logger::Log(Logger::ELevel::ERROR, "Invalid variable [%: %] requested type [%]", _VariableName, pVariable->GetType().GetName(), Foundation::StaticType<T>::Value().GetName());
      }
		}

		return bOk;
	}

	///
	template <typename T>
	bool GetValuePtr(CName const& _VariableName, T** ppValue_)
	{
		assert(ppValue_ != nullptr);

		bool bOk = false;

		CVariable const* pVariable = GetClass().GetVariable(_VariableName);
		if (pVariable != nullptr)
		{
      if (pVariable->GetType().IsKindOf(StaticType<T>::Value()))
      {
        *ppValue_ = static_cast<T*>(pVariable->GetValuePtr(this));
      }
      else
      {
        Logger::Log(Logger::ELevel::ERROR, "Invalid variable [%: %] requested type [%]", _VariableName, pVariable->GetType().GetName(), Foundation::StaticType<T>::Value().GetName());
      }
		}

		return bOk;
	}

private:


};

// Access to dynamic type
template <>
inline Foundation::CType const& GetDynamicType(Foundation::CObject const& _oValue)
{
  return _oValue.GetClass();
}

  
} // Foundation

DECLARE_CLASS_EX(Foundation, CObject)

#endif /* OBJECT_H_ */
