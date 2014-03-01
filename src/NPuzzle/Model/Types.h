#ifndef NPUZZLE_TYPES_H_
#define NPUZZLE_TYPES_H_

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace NPuzzle { namespace Model {

typedef boost::geometry::model::d2::point_xy<int> V2i;

} } // NPuzzle::Model

//====================================
// Serialization
//====================================
namespace boost { namespace serialization {

template<class Archive>
void serialize(Archive & _Archive, NPuzzle::Model::V2i& _V2i, const unsigned int _uVersion)
{
	_Archive & boost::serialization::make_nvp("x", _V2i.x());
	_Archive & boost::serialization::make_nvp("y", _V2i.y());
}

} } // boost::serialization

#endif // NPUZZLE_TYPES_H_
