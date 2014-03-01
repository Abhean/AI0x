/*
 * ITypedObjectPool.h
 *
 *  Created on: Feb 28, 2012
 *      Author: kique
 */

#ifndef IOBJECT_POOL_H_
#define IOBJECT_POOL_H_

#include "Foundation/IObjectPtr.h"

namespace Foundation
{

// Forward declarations
class CObject;

/// Pool of typed objects
class IObjectPool
{
public:

	// THandle
	typedef unsigned short THandle;
	static THandle const INVALID_HANDLE = -1;

	virtual ~IObjectPool() { /* ... */ }

	virtual THandle		  Alloc() = 0;
	virtual void		  Free(THandle _hInstance) = 0;

	virtual CObject*     Lock   (THandle _hInstance) = 0;
	virtual void 		  Unlock (THandle _hInstance) = 0;
	virtual bool 		  IsLocked () const = 0;
};

//
} // Foundation

#endif /* IOBJECT_POOL_H_ */
