/*
 * Class.h
 *
 *  Created on: Oct 24, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_CLASS_H_
#define FOUNDATION_CLASS_H_

#include "Variable.h"
#include "Name.h"
#include "Type.h"
#include <unordered_map>
#include <type_traits>


namespace Foundation
{

class CClass;

template<typename T>
struct HasPopulateMethod
{
        template<typename U, void (*)(CClass*)> struct SFINAE {};
        template<typename U> static char Test(SFINAE<U, &U::Populate>*);
        template<typename U> static int Test(...);
        static const bool Value = sizeof(Test<T>(0)) == sizeof(char);
};

///
class CClass : public CType
{
  DECLARE_DYNAMIC_TYPE(CClass)
  
public:
	//----------------------------------------
	// Types
	//----------------------------------------

	typedef std::function<void (CClass*)> TPopulate;

  //----------------------------------------
  // Initialization / Destruction
  //----------------------------------------
  
  // Populate method [optional]
	template <typename T>
	CClass(T* _pTypeDummy, CNameLiteral&& _oName, CNameLiteral&& _oSupertypeName, typename std::enable_if< HasPopulateMethod<T>::Value >::type* = 0 ) :
	CClass(_pTypeDummy, std::forward<CNameLiteral>(_oName), T::CreateInstance, std::forward<CNameLiteral>(_oSupertypeName), &T::Populate)
	{ /* ... */	}

	// No Populate method [optional]
	template <typename T>
	CClass(T* _pTypeDummy, CNameLiteral&& _oName, CNameLiteral&& _oSupertypeName,  typename std::enable_if< !HasPopulateMethod<T>::Value >::type* = 0 ) :
	CClass(_pTypeDummy, std::forward<CNameLiteral>(_oName), T::CreateInstance, std::forward<CNameLiteral>(_oSupertypeName), nullptr)
	{ /* ... */	}


	template <typename T>
	CClass(T* _pTypeDummy, CNameLiteral&& _oName, CType::TCreateInstance const& _fnCreateInstance, CNameLiteral&& _oSupertypeName, TPopulate const& _fnPopulate) :
	CClass(std::forward<CNameLiteral>(_oName), sizeof(T), _fnCreateInstance, std::forward<CNameLiteral>(_oSupertypeName), _fnPopulate)
	{ /* ... */ }

	CClass(CNameLiteral&& _oName, unsigned _uSize, TCreateInstance const& _fnCreateInstance, CNameLiteral&& _oSupertypeName, TPopulate const& _fnPopulate);
	///

	virtual ~CClass();

	///
  virtual void Populate(CTypeRegistry const* _pTypeRegistry);

	//----------------------------------------
	// Member management
	//----------------------------------------

  ///
  template <typename T>
  void AddVariable(CName const& _Name, unsigned _uOffset);
  
  ///
	void AddVariable(CName const& _Name, CType const& _oType, unsigned _uOffset);
 
  ///
	CVariable const* GetVariable(CName const& _Name) const;

private:

	typedef CType Base;

	TPopulate const  m_fnPopulate;

	// @REVIEW[egarcia]: It would be useful to have the fields in the offset order (serialization, etc.)
	typedef std::unordered_map<CName, std::unique_ptr<CVariable>> TVariableMap;

	TVariableMap	 m_mapVariables;

};

//----------------------------------------
// Templates impl
//----------------------------------------

///
template <typename T>
void CClass::AddVariable(CName const& _Name, unsigned _uOffset)
{ 
  AddVariable(_Name, Foundation::StaticType<T>::Value(), _uOffset);
}

} /* namespace Foundation */

//----------------------------------------------
// MACROS
//----------------------------------------------

// DECLARE_CLASS macro
#define DECLARE_CLASS(CLASS, BASE_CLASS) \
	public:\
	virtual Foundation::CClass const& GetClass() const { return CLASS::s_oClass; }\
	static Foundation::CType const& GetStaticType() { return CLASS::s_oClass; }\
	static CLASS* CreateInstance() { return new CLASS(); }\
	private:\
        typedef BASE_CLASS Super;\
	static Foundation::CClass s_oClass;


// IMPLEMENT_CLASS macro
#define IMPLEMENT_CLASS(CLASS, BASE_CLASS) \
	Foundation::CClass CLASS::s_oClass(static_cast<CLASS*>(nullptr), Foundation::CNameLiteral(#CLASS), Foundation::CNameLiteral(#BASE_CLASS));

	
// DECLARE_CLASS_EX macro
#define DECLARE_CLASS_EX(NAMESPACE, CLASS) \
  namespace NAMESPACE {\
    struct CLASS##_Class {\
      static Foundation::CType const& GetStaticType() { return CLASS##_Class::s_oClass; }\
      static Foundation::CClass s_oClass; \
    };\
  } \
  namespace Foundation { \
    template <>\
    struct StaticType<NAMESPACE::CLASS> \
    {\
    static CType const& Value() { return NAMESPACE::CLASS##_Class::s_oClass; }\
    };\
    template <>\
    struct StaticType<NAMESPACE::CLASS const> \
    {\
    static CType const& Value() { return NAMESPACE::CLASS##_Class::s_oClass; }\
    };\  
  } 
 
// IMPLEMENT_CLASS_EX macro
#define IMPLEMENT_CLASS_EX(NAMESPACE, CLASS, BASE_CLASS, FN_CREATE_INSTANCE, FN_POPULATE) \
  namespace NAMESPACE {\
    Foundation::CClass CLASS##_Class::s_oClass(static_cast<CLASS*>(nullptr), Foundation::CNameLiteral(#NAMESPACE"::"#CLASS), FN_CREATE_INSTANCE, Foundation::CNameLiteral(#BASE_CLASS), FN_POPULATE); \
  } // namespace Foundation
  
#endif /* FOUNDATION_CLASS_H_ */

