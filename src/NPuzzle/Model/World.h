/*
 * WorldModel.h
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */
#ifndef NPUZZLE_MODEL_WORLD_H_
#define NPUZZLE_MODEL_WORLD_H_

#include "AI/Model/World.h"
#include "NPuzzle/Model/Types.h"

namespace NPuzzle { namespace Model {

class CWorld: public AI::Model::IWorld
{
public:

	/// ESlideDirection
	enum class ESlideDirection : unsigned char
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		// ...
		COUNT,
		INVALID = 0x7F
	};


	   	   	   CWorld (const V2i& _v2GridSize);
			   CWorld ();
	virtual   ~CWorld ();

	bool 	   CanSlideTile (V2i const& _TilePos, ESlideDirection _eSlideDirection) const;
	V2i const& GetGridSize  () const { return m_v2GridSize; }

private:

	V2i m_v2GridSize;

	//====================================
	// Serialization
	//====================================
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & _Archive, const unsigned int _uVersion)
	{
		_Archive & boost::serialization::make_nvp("GridSize", m_v2GridSize);
	}
};

} } // NPuzzle::Model


#endif /* NPUZZLE_MODEL_WORLD_H_ */
