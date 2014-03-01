/*
 * Types.h
 *
 *  Created on: Feb 19, 2012
 *      Author: kique
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <boost/geometry.hpp>
#include "TypeRegistry.h"
#include "Name.h"
#include "Pointer.h"
#include <string>

typedef boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian> V2i;
typedef boost::geometry::model::point<float, 3, boost::geometry::cs::cartesian> V3f;

// Primitive types
DECLARE_PRIMITIVE_TYPE(int);
DECLARE_PRIMITIVE_TYPE(float);
DECLARE_PRIMITIVE_TYPE(bool);
DECLARE_PRIMITIVE_TYPE_EX(void);

// Non Object Types
DECLARE_STATIC_TYPE(Foundation, CName);
DECLARE_STATIC_TYPE(std, string);


DECLARE_PRIMITIVE_POINTER_TYPE(void);

// Conversions


#endif /* TYPES_H_ */
