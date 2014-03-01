/*
 * NameManager.h
 *
 *  Created on: Dec 27, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_NAMEMANAGER_H_
#define FOUNDATION_NAMEMANAGER_H_

#include "Name.h"
#include "NameLiteral.h"
#include "Singleton.h"
#include <unordered_map>
#include <boost/intrusive/list.hpp>

namespace Foundation
{

class CNameManager : public CSingleton<CNameManager>
{
public:

        CNameManager();
	virtual ~CNameManager();

#ifndef NAME_COMPILE_TIME_HASH

	static void RegisterLiteral(CNameLiteral& _oName_);

	// Static Type List
	static void StaticLiteralListInsert (CNameLiteral& _oName_);

	typedef boost::intrusive::member_hook<CNameLiteral, CNameLiteral::TListHook, &CNameLiteral::m_ListHook> TNameLiteralListHookOption;
	typedef boost::intrusive::list<CNameLiteral, TNameLiteralListHookOption, boost::intrusive::cache_last<true>> TNameLiteralList;

	static TNameLiteralList& GetStaticLiteralList()
	{
	    static TNameLiteralList LiteralList;
	    return LiteralList;
	}

	/// String Map
	// string copy
	void StringTableInsert(unsigned _uHash, char const* _pszString);
	// string move
	void StringTableInsert(unsigned _uHash, std::string&& _sString);
	std::string StringTableGet   (unsigned _uHash);

private:

	typedef std::unordered_map<unsigned, std::string const> THashToStringMap;

	// Hash To string Map
	THashToStringMap m_HashToStringMap;
#endif // NAME_COMPILE_TIME_HASH
};

} // namespace Foundation 
#endif /* FOUNDATION_NAMEMANAGER_H_ */
