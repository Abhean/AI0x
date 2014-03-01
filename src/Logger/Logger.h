/*
 * Log.h
 *
 *  Created on: Feb 19, 2012
 *      Author: kique
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace Logger
{
	/// ELevel
	enum class ELevel : unsigned char
	{
		INFO,
		WARNING,
		ERROR,
		// ...
		COUNT,
		INVALID = 0x7F
	};

	static char const* pszLEVEL_NAME[static_cast<unsigned>(ELevel::COUNT)] =
	{
	  "INFO",
	  "WARNING",
	  "ERROR"
	};


	inline void _LogMessage(char const* _pszMessage)
	{
		while (*_pszMessage != 0)
		{
			if (*_pszMessage == '%' && *(++_pszMessage) != '%')
			{
				std::cout << "[Log:MISSING_PARAM]";
			}

			std::cout << *_pszMessage++;
		}
	}

	template <typename T, typename... Args>
	void _LogMessage(char const* _pszMessage, T const& _Param1, Args const&... _ParamRest)
	{
		while (*_pszMessage != 0)
		{
			if (*_pszMessage == '%' && *(++_pszMessage) != '%')
			{
				std::cout << _Param1;
				_LogMessage(_pszMessage, _ParamRest...);
				break;
			}

			std::cout << *_pszMessage++;
		}
	}

	template <typename... Args>
	void Log(ELevel _eLevel, char const* _pszMessage, Args const&... _Params)
	{
		assert((_eLevel < ELevel::COUNT) && (_pszMessage != 0));

		std::cout << pszLEVEL_NAME[static_cast<unsigned>(_eLevel)] << ": ";

		_LogMessage(_pszMessage, _Params...);

		std::cout << std::endl;
	}


	template <typename... Args>
	void Log(std::vector<std::string> const& _vectTags, ELevel _eLevel, char const* _pszMessage, Args const&... _Params)
	{
		assert((_eLevel < ELevel::COUNT) && (_pszMessage != 0));

		std::cout << "[";
		for (auto ItTag = _vectTags.begin(); ItTag != _vectTags.end(); ++ItTag)
		{
			if (ItTag != _vectTags.begin())
			{
				std::cout << ",";
			}
			std::cout << *ItTag;
		}

		std::cout << "]:";
		std::cout << pszLEVEL_NAME[static_cast<unsigned>(_eLevel)] << ": ";

		_LogMessage(_pszMessage, _Params...);

		std::cout << std::endl;
	}


} // Logger


#endif /* LOGGER_LOGGER_H_ */
