#include "TypeCast.h"
#include "TypeRegistry.h"


namespace Foundation 
{
  
STypeCastEntry::STypeCastEntry(char const* _pszSourceType, char const* _pszTargetType, TTypeCast const& _fnCast) :
  nSourceType(_pszSourceType),
  nTargetType(_pszTargetType),
  fnCast(_fnCast)
{
  // Add Type to static list
  CTypeRegistry::StaticTypeCastListAdd(*this);
}

STypeCastEntry::STypeCastEntry(STypeCastEntry const& _oTypeCastEntry) :
  nSourceType(_oTypeCastEntry.nSourceType.GetString()),
  nTargetType(_oTypeCastEntry.nTargetType.GetString()),
  fnCast(_oTypeCastEntry.fnCast)
{

}


} // namespace Foundation