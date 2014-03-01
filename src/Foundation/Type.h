/*
 * Type.h
 *
 *  Created on: Feb 19, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_TYPE_H_
#define FOUNDATION_TYPE_H_

#include "TypeCast.h"
#include "NameLiteral.h"
#include "Logger/Logger.h"
#include <boost/intrusive/slist.hpp>
#include <functional>
#include <map>
#include <type_traits>

//----------------------------------------------
// MACROS
//----------------------------------------------

// DECLARE_DYNAMIC_TYPE macro
#define DECLARE_DYNAMIC_TYPE(TYPE) \
public:\
  virtual Foundation::CType const& GetDynamicType() const { return TYPE::s_oType; }\
  static Foundation::CType const& GetStaticType() { return TYPE::s_oType; }\
  private:\
  static Foundation::CType s_oType;
    
    
// IMPLEMENT_DYNAMIC_TYPE macro
#define IMPLEMENT_DYNAMIC_TYPE(TYPE, SUPERTYPE) \
  Foundation::CType TYPE::s_oType(static_cast<TYPE*>(nullptr), Foundation::CNameLiteral(#TYPE), Foundation::CNameLiteral(#SUPERTYPE), nullptr);


/// DECLARE_STATIC_TYPE macro
#define DECLARE_STATIC_TYPE(NAMESPACE, TYPE) \
  namespace NAMESPACE { \
    struct TYPE##_Type\
    {\
      static Foundation::CType s_oType;\
    };\
  }\
  namespace Foundation {\
    template <>\
    struct StaticType<NAMESPACE::TYPE> \
    {\
      static CType const& Value() { return NAMESPACE::TYPE##_Type::s_oType; }\
    };\
    template <>\
    struct StaticType<NAMESPACE::TYPE const> \
    {\
    static CType const& Value() { return NAMESPACE::TYPE##_Type::s_oType; }\
    };\
  }

#define IMPLEMENT_STATIC_TYPE(NAMESPACE, TYPE, FN_CREATE_INSTANCE)\
  namespace NAMESPACE {\
    Foundation::CType  TYPE##_Type::s_oType { static_cast<TYPE*>(nullptr), Foundation::CNameLiteral(#NAMESPACE"::"#TYPE), Foundation::CNameLiteral(""), FN_CREATE_INSTANCE };\
  }

/// DECLARE_PRIMITIVE_TYPE
#define DECLARE_PRIMITIVE_TYPE(TYPE) \
  struct TYPE##_Type\
  {\
    static TYPE* CreateInstance() { return new TYPE(); }\
    static Foundation::CType  s_oType;\
  };\
  namespace Foundation {\
    template <> \
    struct StaticType<TYPE>\
    {\
      static CType const& Value() { return TYPE##_Type::s_oType; }\
    };\
    template <> \
    struct StaticType<TYPE const>\
    {\
    static CType const& Value() { return TYPE##_Type::s_oType; }\
    };\
    }

/// IMPLEMENT_PRIMITIVE_TYPE
#define IMPLEMENT_PRIMITIVE_TYPE(TYPE)\
Foundation::CType TYPE##_Type::s_oType { static_cast<TYPE*>(nullptr), Foundation::CNameLiteral(#TYPE), Foundation::CNameLiteral(""), &TYPE##_Type::CreateInstance };  


/// DECLARE_PRIMITIVE_TYPE_EX
#define DECLARE_PRIMITIVE_TYPE_EX(TYPE) \
struct TYPE##_Type\
{\
static Foundation::CType  s_oType;\
};\
namespace Foundation {\
template <> \
struct StaticType<TYPE>\
{\
static CType const& Value() { return TYPE##_Type::s_oType; }\
};\
template <> \
struct StaticType<TYPE const>\
{\
static CType const& Value() { return TYPE##_Type::s_oType; }\
};\
}

/// IMPLEMENT_PRIMITIVE_TYPE_EX
#define IMPLEMENT_PRIMITIVE_TYPE_EX(TYPE, CREATE_INSTANCE)\
Foundation::CType TYPE##_Type::s_oType { static_cast<TYPE*>(nullptr), Foundation::CNameLiteral(#TYPE), Foundation::CNameLiteral(""), CREATE_INSTANCE };  
  
namespace Foundation
{

class CTypeRegistry;
class CType;
  
//----------------------------------------------
// Utility
//----------------------------------------------  

template <typename T>
struct StaticType
{
  static CType const& Value()
  {
    return T::GetStaticType();
  }
};


// template <typename T>
// struct StaticType<T*>
// {
//   static CType const& Value()
//   {
//     static_assert(false, "You must to specialize StaticType for each pointer type.");
//   }
// };



template <typename T>
CType const& GetDynamicType(T const& _Value)
{
  return _Value.GetDynamicType();
};

//-------------------------------------------
// CType
//-------------------------------------------

///
class CType
{
  DECLARE_DYNAMIC_TYPE(CType)
    
public:

	// Types
	typedef std::function<void* ()> TCreateInstance;
	typedef std::function<bool (void const* _pSourceValue, CType const& _oTargetType, void* pTargetValue_)> TCastValue;

  // Safe casting
  template <typename TTarget, typename TSource>
  static TTarget* DynamicCast(TSource* _pValue)
  {
    return (_pValue != nullptr) && Foundation::GetDynamicType(*_pValue).IsKindOf(Foundation::StaticType<TTarget>::Value()) ? static_cast<TTarget*>(_pValue) : nullptr;
  }
  
  template <typename TTarget, typename TSource>
  static TTarget const* DynamicCast(TSource const* _pValue) 
  {
    return (_pValue != nullptr) && Foundation::GetDynamicType(*_pValue).IsKindOf(Foundation::StaticType<TTarget>::Value()) ? static_cast<TTarget const*>(_pValue) : nullptr;
  }
  
	//-------------------------------------------
	// Initialization / Destruction
	//-------------------------------------------
	template <typename T>
	CType(T* _pTypeDummy, CNameLiteral&& _oName, CNameLiteral&& _oSupertypeName, TCreateInstance const& _fnCreateInstance) :
    CType(std::forward<CNameLiteral>(_oName), sizeof(T), std::forward<CNameLiteral>(_oSupertypeName), _fnCreateInstance)
    { /* ... */ }

	///
	CType(CNameLiteral&& _oName, unsigned _uSize, CNameLiteral&& _oSupertypeName, TCreateInstance const& _fnCreateInstance);

	///
	virtual ~CType();
 
	///
	virtual void Populate(CTypeRegistry const* _pTypeRegistry);

	///
	bool IsKindOf(CType const& _Type) const;

	///
	CNameLiteral const& GetName() const;

	///
	unsigned GetSize() const;

  ///
  template <typename T>
  bool GetValue(void const* _pObject, T* pValue_) const;
  
  ///
  template <typename T>
  bool SetValue(void* pObject_, T _Value) const;
  
	///
	bool operator==(CType const& _Type) const;

	///
	template <typename T>
	T* CreateInstance() const;

	///
	void* CreateInstance() const;

  ///  
  TTypeCast GetTypeCast(CName const& _nTarget) const;
  
  ///
  void RegisterTypeCast(CName const& _nTarget, TTypeCast const& _fnCast);
  

private:
  
  typedef std::map<CName, TTypeCast> TTypeCastMap;
  typedef TTypeCastMap::const_iterator TTypeCastMapConstIt;
  typedef TTypeCastMap::iterator TTypeCastMapIt;
  
  ///
	CNameLiteral m_oName;

	///
	unsigned m_uSize;

  ///
  CNameLiteral m_oSupertypeName;
  CType const* m_pSupertype;
  
	///
	TCreateInstance const  m_fnCreateInstance;
  
  // TypeCasts
  TTypeCastMap m_TypeCastMap;

  // TypeRegistry List Hook
  friend class CTypeRegistry;
 
  typedef boost::intrusive::slist_member_hook<boost::intrusive::link_mode<boost::intrusive::safe_link>> TListHook;
  TListHook  m_ListHook;
  
};

//----------------------------------------
// inline impl
//----------------------------------------

///
inline bool CType::operator==(CType const& _Type) const
{
	return &_Type == this;
}

///
inline CNameLiteral const& CType::GetName() const
{
	return m_oName;
}

///
inline unsigned CType::GetSize() const
{
	return m_uSize;
}

//----------------------------------------
// Templates impl
//----------------------------------------

///
template <typename T>
T* CType::CreateInstance() const
{
	T* pInstance = nullptr;

  if (Foundation::StaticType<T>::Value().IsKindOf(*this))
	{
		void* pInstanceData = CreateInstance();
		if   (pInstanceData != nullptr)
		{
			pInstance = reinterpret_cast<T*>(pInstanceData);
		}
	}

	return pInstance;
}


///
template <typename T>
bool CType::GetValue(void const* _pValuePtr, T* pValue_) const
{
  bool bOk = false; // @REVIEW[egarcia]: Throw exception if invalid type?
  
  if (Foundation::StaticType<T>::Value() == *this)
  {
    *pValue_ = *reinterpret_cast<T const*>(_pValuePtr);
    bOk = true;
  }
  else
  {
    TTypeCast fnCast = GetTypeCast(Foundation::StaticType<T>::Value().GetName());
    if (fnCast != nullptr) 
    {
      bOk = fnCast(_pValuePtr, reinterpret_cast<void*>(pValue_));
    }
    else
    {
      Logger::Log(Logger::ELevel::ERROR, "Invalid variable [%: %] requested type [%]", GetName(), GetName(), Foundation::StaticType<T>::Value().GetName());
    }
  }
  
  return bOk;
}

///
template <typename T>
bool CType::SetValue(void* pValuePtr_, T _Value) const
{
  bool bOk = false; // @REVIEW[egarcia]: Throw exception if invalid type?
  
  if (Foundation::StaticType<T>::Value() == *this)
  {
    *reinterpret_cast<T*>(pValuePtr_) = _Value;
    bOk = true;
  }
  else
  {
    TTypeCast fnCast = Foundation::StaticType<T>::Value().GetTypeCast(GetName());
    if (fnCast != nullptr) 
    {
      bOk = fnCast(reinterpret_cast<void const*>(&_Value), pValuePtr_);
    }
    else
    {
      Logger::Log(Logger::ELevel::ERROR, "Invalid variable [%: %] requested type [%]", GetName(), GetName(), Foundation::StaticType<T>::Value().GetName());
    }
  }
  
  return bOk;
}

} // Foundation

 
#endif /* FOUNDATION_TYPE_H_ */
