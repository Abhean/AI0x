/*
 * Archive.h
 *
 *  Created on: 02/11/2012
 *      Author: kique
 */

#ifndef SERIALIZATION_DATASTREAM_H_
#define SERIALIZATION_DATASTREAM_H_

#include <iostream>
#include <vector>
#include <memory>

// Forward Declarations
namespace Foundation
{
	class CObject;
}

// IDataStream
namespace Serialization
{

class IDataStream
{
public:
	virtual ~IDataStream() { /* ... */ }

};

} /* namespace Serialization */
#endif /* SERIALIZATION_DATASTREAM_H_ */
