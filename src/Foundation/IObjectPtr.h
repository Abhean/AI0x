/*
 * IObjectPtr.h
 *
 *  Created on: Feb 28, 2012
 *      Author: kique
 */

#ifndef IOBJECT_PTR_H_
#define IOBJECT_PTR_H_

namespace Foundation
{

// Concept?
class IObjectPtr
{
public:

	virtual ~IObjectPtr() = 0;

	//virtual operator *() = 0;
};

// Destructor default implementation
inline IObjectPtr::~IObjectPtr()
{
	/* ... */
}

} // namespace Foundation

#endif // IOBJECT_PTR_H_
