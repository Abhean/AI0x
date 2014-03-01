/*
 * Variable.cpp
 *
 *  Created on: Oct 21, 2012
 *      Author: kique
 */

#include "Variable.h"

namespace Foundation
{

CVariable::CVariable(CName _Name, CType const& _Type, unsigned _uOffset) :
		CField(_Name),
		m_Type(_Type),
		m_uOffset(_uOffset)
{

}

CVariable::~CVariable()
{
	// TODO Auto-generated destructor stub
}

} /* namespace Foundation */
