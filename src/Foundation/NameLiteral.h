/*
 * NameStatic.h
 *
 *  Created on: Dec 27, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_NAMESTATIC_H_
#define FOUNDATION_NAMESTATIC_H_

#include "Name.h"
#include <boost/intrusive/list.hpp>

namespace Foundation
{

// Name
class CNameLiteral : public CName
{
public:

	explicit NAME_CONSTEXPR CNameLiteral(char const* _pszName);

#ifndef NAME_COMPILE_TIME_HASH
	~CNameLiteral();
#endif

	CNameLiteral(CNameLiteral&& _oNameLiteral) noexcept;

	///
	NAME_CONSTEXPR char const* GetString() const
	{
		return m_pszName;
	}

	///
	friend std::ostream& operator<<(std::ostream& _oOutStream_, CNameLiteral const& _Name);

#ifndef NAME_COMPILE_TIME_HASH
	// NameLiteral List Hook
	typedef boost::intrusive::list_member_hook<boost::intrusive::link_mode<boost::intrusive::safe_link>> TListHook;
	TListHook  m_ListHook;
#endif // NAME_STATIC_LIST

private:

	char const* m_pszName;
};


///
#ifdef NAME_COMPILE_TIME_HASH
inline constexpr CNameLiteral::CNameLiteral(char const* _pszName) :
	CName(_pszName),
	m_pszName(_pszName)
{ /* ... */ }
#endif //NAME_COMPILE_TIME_HASH

///
inline NAME_CONSTEXPR Foundation::CName operator "" _n(char const* str, size_t /*length*/)
{
    return Foundation::CName(str);
}

} // namespace Foundation 
#endif /* NAMESTATIC_H_ */
