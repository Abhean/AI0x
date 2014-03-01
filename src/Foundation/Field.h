/*
 * Field.h
 *
 *  Created on: Oct 21, 2012
 *      Author: kique
 */

#ifndef FOUNDATION_FIELD_H_
#define FOUNDATION_FIELD_H_

#include "Name.h"

namespace Foundation
{

class CField
{
public:
		 CField(CName _Name);
	virtual ~CField();

	CName const& GetName() const { return m_Name; }

private:

	CName m_Name;

};

} /* namespace Foundation */
#endif /* FOUNDATION_FIELD_H_ */
