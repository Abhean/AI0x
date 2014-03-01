/*
 * WorldModel.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#include "World.h"

namespace NPuzzle { namespace Model {


CWorld::CWorld(const V2i & _v2GridSize) :
	m_v2GridSize(_v2GridSize)
{
}

CWorld::CWorld() : /*CWorld(V2i(0, 0))*/
	m_v2GridSize(V2i(0, 0))
{
	// TODO Auto-generated constructor stub

}


CWorld::~CWorld()
{
	// TODO Auto-generated destructor stub
}

bool CWorld::CanSlideTile(const V2i & _TilePos, ESlideDirection _eSlideDirection) const
{
	bool bCanSlideTile = false;

	switch (_eSlideDirection)
	{
		case CWorld::ESlideDirection::DOWN  : { bCanSlideTile = (_TilePos.y() < (m_v2GridSize.y() - 1)); } break;
		case CWorld::ESlideDirection::UP    : { bCanSlideTile = (_TilePos.y() > 0); } break;
		case CWorld::ESlideDirection::RIGHT : { bCanSlideTile = (_TilePos.x() < (m_v2GridSize.x() - 1)); } break;
		case CWorld::ESlideDirection::LEFT  : { bCanSlideTile = (_TilePos.x() > 0); } break;
		default:
		{
			assert(false);
		}
		break;
	}

	return bCanSlideTile;

}

} } // namespace NPuzzle::Model
