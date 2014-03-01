/*
 * TypeRegistry.h
 *
 *  Created on: Feb 19, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_TYPEREGISTRY_H_
#define FOUNDATION_TYPEREGISTRY_H_

#include "Singleton.h"
#include "Type.h"
#include "TypeCast.h"
#include "Name.h"
#include <boost/intrusive/slist.hpp>
#include <map>

// Forward declarations
namespace Foundation
{

class CTypeRegistry : public CSingleton<CTypeRegistry>
{
public:

  CTypeRegistry();
  ~CTypeRegistry();

  void         RegisterType  (CType* _pType, bool _bOwner);

  CType const* GetTypeByName (CName const& _Name) const;
  CType*       GetTypeByName (CName const& _Name);
  
  static void  StaticTypeListAdd(CType& _oType_);
  static void  StaticTypeCastListAdd(STypeCastEntry& _oTypeCastEntry_);

private:

  // Static Type List
  typedef boost::intrusive::member_hook<CType, CType::TListHook, &CType::m_ListHook> TTypeListHookOption;
  typedef boost::intrusive::slist<CType, TTypeListHookOption, boost::intrusive::cache_last<true>> TTypeList;

  static TTypeList& GetStaticTypeList()
  {
      static TTypeList List;
      return List;
  }

  // Static TypeCast List
  typedef boost::intrusive::member_hook<STypeCastEntry, STypeCastEntry::TListHook, &STypeCastEntry::oListHook> TTypeCastListHookOption;
  typedef boost::intrusive::slist<STypeCastEntry, TTypeCastListHookOption, boost::intrusive::cache_last<true>> TTypeCastList;

  static TTypeCastList& GetStaticTypeCastList()
  {
      static TTypeCastList List;
      return List;
  }

  // Type Entry
  class CTypeEntry
  {
  public:
    
    CTypeEntry(CType* _pType, bool _bOwner) :
      m_pType(_pType),
      m_bOwner(_bOwner)
    { /* ... */ }
      
    ~CTypeEntry()
    {
      if (m_bOwner)
      {
        delete m_pType;
      }
    }
    
    CTypeEntry(CTypeEntry&& _oEntry_) :
      m_pType(_oEntry_.m_pType),
      m_bOwner(_oEntry_.m_bOwner)
    {
      _oEntry_.m_pType = nullptr;
      _oEntry_.m_bOwner = false;
    }
    
    CTypeEntry(CTypeEntry const& _oEntry) = delete;
    CTypeEntry& operator=(CTypeEntry const& _oEntry) = delete;
    
    CType* GetType() const { return m_pType; }
      
  private:
    
    CType* m_pType;
    bool   m_bOwner;
  };

  // Types
  typedef std::map<CName, CTypeEntry> TTypeMap;
  

  typedef TTypeMap::const_iterator TTypeMapConstIt;
  typedef TTypeMap::iterator       TTypeMapIt;

  TTypeMap m_TypeMap;
};

} // Foundation


#endif /* FOUNDATION_TYPEREGISTRY_H_ */
