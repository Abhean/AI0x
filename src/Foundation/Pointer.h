#ifndef FOUNDATION_POINTER_H_
#define FOUNDATION_POINTER_H_

#include "Name.h"
#include "Type.h"
#include <unordered_map>
#include <type_traits>


/// DECLARE_PRIMITIVE_POINTER_TYPE
#define DECLARE_PRIMITIVE_POINTER_TYPE(TYPE)\
struct TYPE##_POINTER_Type\
{\
  static TYPE** CreateInstance() { return new TYPE*(); }\
  static Foundation::CPointer s_oType;\
};\
namespace Foundation {\
  template <> \
  struct StaticType<TYPE*>\
  {\
    static CType const& Value() { return TYPE##_POINTER_Type::s_oType; }\
  };\
  template <> \
  struct StaticType<TYPE* const>\
  {\
    static CType const& Value() { return TYPE##_POINTER_Type::s_oType; }\
  };\
}

/// IMPLEMENT_PRIMITIVE_POINTER_TYPE
#define IMPLEMENT_PRIMITIVE_POINTER_TYPE(TYPE)\
Foundation::CPointer TYPE##_POINTER_Type::s_oType { Foundation::CNameLiteral(#TYPE"*"), sizeof(TYPE*), Foundation::CNameLiteral(""), &TYPE##_POINTER_Type::CreateInstance, Foundation::StaticType<TYPE>::Value() };  

/// DECLARE_POINTER_TYPE 
#define DECLARE_POINTER_TYPE(NAMESPACE, TYPE) \
namespace NAMESPACE { \
struct TYPE##_POINTER_Type\
{\
static TYPE** CreateInstance() { return new TYPE*(); }\
static Foundation::CPointer s_oType;\
};\
}\
namespace Foundation {\
template <>\
struct StaticType<NAMESPACE::TYPE*> \
{\
static CType const& Value() { return NAMESPACE::TYPE##_POINTER_Type::s_oType; }\
};\
template <>\
struct StaticType<NAMESPACE::TYPE* const> \
{\
static CType const& Value() { return NAMESPACE::TYPE##_POINTER_Type::s_oType; }\
};\
}

/// IMPLEMENT_POINTER_TYPE 
#define IMPLEMENT_POINTER_TYPE(NAMESPACE, TYPE)\
namespace NAMESPACE {\
Foundation::CPointer  TYPE##_POINTER_Type::s_oType { Foundation::CNameLiteral(#NAMESPACE"::"#TYPE"*"), sizeof(TYPE*), Foundation::CNameLiteral(""), &TYPE##_POINTER_Type::CreateInstance, Foundation::StaticType<TYPE>::Value() };\
}

/// DECLARE_POINTER_TYPE_EX
#define DECLARE_POINTER_TYPE_EX(NAMESPACE, TYPE) \
namespace NAMESPACE { \
struct TYPE##_Type\
{\
static TYPE* CreateInstance() { return new TYPE(); }\
static Foundation::CPointer s_oType;\
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

/// IMPLEMENT_POINTER_TYPE_EX
#define IMPLEMENT_POINTER_TYPE_EX(NAMESPACE, TYPE, POINTED_TYPE_NAMESPACE, POINTED_TYPE)\
namespace NAMESPACE {\
Foundation::CPointer  TYPE##_Type::s_oType { Foundation::CNameLiteral(#NAMESPACE"::"#TYPE), sizeof(TYPE), Foundation::CNameLiteral(""), &TYPE##_Type::CreateInstance, Foundation::StaticType<POINTED_TYPE_NAMESPACE::POINTED_TYPE>::Value() };\
}

namespace Foundation
{
  
///
class CPointer : public CType
{
  DECLARE_DYNAMIC_TYPE(CPointer)
  
public:
  
  CPointer(CNameLiteral&& _oName, unsigned _uSize, CNameLiteral&& _oSupertypeName, TCreateInstance const& _fnCreateInstance, CType const& _oPointedType) :
    CType(std::forward<CNameLiteral>(_oName), _uSize, std::forward<CNameLiteral>(_oSupertypeName), _fnCreateInstance),
    m_oPointedType(_oPointedType)
    { /* ... */ }
  
  inline CType const& GetPointedType() const { return m_oPointedType; }
  
  
private:
  
  CType const& m_oPointedType; 
};

} // namespace Foundation

#endif // FOUNDATION_POINTER_H_