#include "Types.h"
#include "TypeCast.h"
#include <string>

// Non Object Types
IMPLEMENT_STATIC_TYPE(Foundation, CName, nullptr);
IMPLEMENT_STATIC_TYPE(std, string, nullptr);

namespace Foundation 
{
//----------------------------------------------
template <>
struct TypeCast<std::string, Foundation::CName>
{
  static bool Apply(void const* _pSource, void* pTarget_)
  {
    *static_cast<CName*>(pTarget_) = Foundation::CName { *static_cast<const std::string*>(_pSource) };
    return true;
  }
};

//----------------------------------------------
template <>
struct TypeCast<std::string, float>
{
  static bool Apply(void const* _pSource, void* pTarget_)
  {
    *static_cast<float*>(pTarget_) = std::stof(static_cast<const std::string*>(_pSource)->c_str());
    return true;
  }
};

} // namespace Foundation

// Primitive Types
IMPLEMENT_PRIMITIVE_TYPE(int);
IMPLEMENT_PRIMITIVE_TYPE(float);
IMPLEMENT_PRIMITIVE_TYPE(bool);
IMPLEMENT_PRIMITIVE_TYPE_EX(void, 0, nullptr);

IMPLEMENT_PRIMITIVE_POINTER_TYPE(void);

// Casts
IMPLEMENT_TYPE_CAST_NST_NST(std, string, Foundation, CName);
IMPLEMENT_TYPE_CAST_T_T(float, int);
IMPLEMENT_TYPE_CAST_NST_T(std, string, float);
