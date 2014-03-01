/*
 * TypeCast.h
 *
 *  Created on: Nov 24, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_TYPECAST_H_
#define FOUNDATION_TYPECAST_H_

#include "Name.h"
#include "NameLiteral.h"
#include <boost/intrusive/slist.hpp>

namespace Foundation
{

typedef std::function<bool (void const* _pSource, void* pTarget_)> TTypeCast;
  
  
struct STypeCastEntry
{
  STypeCastEntry(char const* _pszSourceType, char const* _pszTargetType, TTypeCast const& _fnCast);
  STypeCastEntry(STypeCastEntry const& _oTypeCastEntry);
  
  CNameLiteral nSourceType;
  CNameLiteral nTargetType;
  
  TTypeCast fnCast;
  
  // Type List Hook
  typedef boost::intrusive::slist_member_hook<boost::intrusive::link_mode<boost::intrusive::safe_link>> TListHook;
  TListHook oListHook;
};

//----------------------------------------------
template <typename TSource, typename TTarget>
bool TypeCast(void const* _pSource, void* pTarget_)
{
  *(static_cast<TTarget*>(pTarget_)) = *(static_cast<const TSource*>(_pSource));
  return true;
}

} // namespace Foundation 


//----------------------------------------------
// MACROS
//----------------------------------------------

#define IMPLEMENT_TYPE_CAST_NST_NST(SOURCE_NAMESPACE, SOURCE_TYPE, TARGET_NAMESPACE, TARGET_TYPE) \
Foundation::STypeCastEntry TYPECAST_##SOURCE_NAMESPACE##_##SOURCE_TYPE_2_##TARGET_NAMESPACE##_##TARGET_TYPE(#SOURCE_NAMESPACE"::"#SOURCE_TYPE, #TARGET_NAMESPACE"::"#TARGET_TYPE, &Foundation::TypeCast<SOURCE_NAMESPACE::SOURCE_TYPE, TARGET_NAMESPACE::TARGET_TYPE>);

#define IMPLEMENT_TYPE_CAST_NST_NSPT(SOURCE_NAMESPACE, SOURCE_TYPE, TARGET_NAMESPACE, TARGET_TYPE) \
Foundation::STypeCastEntry TYPECAST_##SOURCE_NAMESPACE##_##SOURCE_TYPE_2_##TARGET_NAMESPACE##_##TARGET_TYPE##_##PTR(#SOURCE_NAMESPACE"::"#SOURCE_TYPE, #TARGET_NAMESPACE"::"#TARGET_TYPE"*", &Foundation::TypeCast<SOURCE_NAMESPACE::SOURCE_TYPE, TARGET_NAMESPACE::TARGET_TYPE*>);

#define IMPLEMENT_TYPE_CAST_NSPT_NST(SOURCE_NAMESPACE, SOURCE_TYPE, TARGET_NAMESPACE, TARGET_TYPE) \
Foundation::STypeCastEntry TYPECAST_##SOURCE_NAMESPACE##_##SOURCE_TYPE_PTR_2_##TARGET_NAMESPACE##_##TARGET_TYPE(#SOURCE_NAMESPACE"::"#SOURCE_TYPE"*", #TARGET_NAMESPACE"::"#TARGET_TYPE, &Foundation::TypeCast<SOURCE_NAMESPACE::SOURCE_TYPE*, TARGET_NAMESPACE::TARGET_TYPE>);

#define IMPLEMENT_TYPE_CAST_NST_T(SOURCE_NAMESPACE, SOURCE_TYPE, TARGET_TYPE) \
Foundation::STypeCastEntry TYPECAST_##SOURCE_NAMESPACE##_##SOURCE_TYPE_2_##TARGET_TYPE(#SOURCE_NAMESPACE"::"#SOURCE_TYPE, #TARGET_TYPE, &Foundation::TypeCast<SOURCE_NAMESPACE::SOURCE_TYPE, TARGET_TYPE>);


#define IMPLEMENT_TYPE_CAST_T_T(SOURCE_TYPE, TARGET_TYPE) \
Foundation::STypeCastEntry TYPECAST__##SOURCE_TYPE_2__##TARGET_TYPE(#SOURCE_TYPE, #TARGET_TYPE, &Foundation::TypeCast<SOURCE_TYPE, TARGET_TYPE>);

//#define IMPLEMENT_TYPE_CAST(SOURCE_TYPE, TARGET_TYPE) \
//Foundation::STypeCastEntry TYPECAST_##SOURCE_TYPE_2_##TARGET_TYPE(#SOURCE_TYPE, #TARGET_TYPE, &Foundation::DefaultTypeCast<SOURCE_TYPE, TARGET_TYPE>);


#endif /* FOUNDATION_TYPECAST_H_ */





