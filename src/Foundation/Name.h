/*
 * NAME.h
 *
 *  Created on: Sep 26, 2011
 *      Author: kique
 */

#ifndef FOUNDATION_NAME_H_
#define FOUNDATION_NAME_H_

#include "Config.h"
#include "CRC32.h"
#include <boost/crc.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

#ifdef NAME_COMPILE_TIME_HASH
#define NAME_CONSTEXPR constexpr
#else
#define NAME_CONSTEXPR
#endif

namespace Foundation
{

/// Name Class.
/// Requirements:
/// Very low memory footprint (unsigned)
/// Fast comparation (O(1))
/// Human friendly Names (generated from strings)
/// Debug capacities (get readable string from Name)
class CName
{
public:

  ///
  CName();

  CName(CName const& _Name);
  CName(CName&& _Name);

  explicit NAME_CONSTEXPR CName(char const* _pszName);
  explicit CName(std::string const& _sName);
  // @TODO[egarcia]: Review argument passing / move
  explicit CName(std::string&& _sName) noexcept;

  ///
  NAME_CONSTEXPR size_t GetHash() const
  {
          return m_uName;
  }

  ///
  bool IsEmpty() const
  {
    return m_uName == 0;
  }
  
  ///
  CName& operator=(CName const& _Name)
  {
          if (&_Name != this)
          {
                  m_uName = _Name.m_uName;
          }

          return *this;
  }

  /// O(1)
  bool operator==(CName const& _Name) const
  {
          return _Name.m_uName == m_uName;
  }

  ///
  bool operator<(CName const& _Name) const
  {
          return m_uName < _Name.m_uName;
  }

  ///
  friend std::ostream& operator<<(std::ostream& _oOutStream_, CName const& _Name);


private:

  unsigned m_uName;
};



inline CName::CName() :
	m_uName()
{
}

/// Copy Constructor
inline CName::CName(CName const& _Name) :
	m_uName(_Name.m_uName)
{
}

/// Move Constructor
inline CName::CName(CName&& _Name) :
	m_uName(_Name.m_uName)
{
}

#ifdef NAME_COMPILE_TIME_HASH
///
inline constexpr CName::CName(char const* _pszName) :
  	m_uName(COMPILE_TIME_CRC32_STR(_pszName))
{
}

#endif



} // namespace Foundation

// std::hash specialization
namespace std
{
	template <>
	class hash<Foundation::CName>
	{
	public:
		size_t operator()(Foundation::CName const& _Name) const
		{
			return _Name.GetHash();
		}
	};
} // namespace std

#endif /* FOUNDATION_NAME_H_ */
