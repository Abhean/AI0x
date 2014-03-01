/*
 * IWorld.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#include "NPuzzle/Model/State.h"
#include "NPuzzle/Model/World.h"

namespace NPuzzle { namespace Model {

//----------------------------------------
CState::CState(CWorld const* _pWorld)
 : m_pWorld(_pWorld),m_vGrid(_pWorld->GetGridSize().x() * _pWorld->GetGridSize().y())
{
  for (unsigned uGridPos = 0; uGridPos < m_vGrid.size(); ++uGridPos)
  {
	  m_vGrid[uGridPos] = uGridPos;
  }

  m_v2EmptySpacePos = V2i(0, 0);
}

//----------------------------------------
CState::~CState()
{
}


} } // namespace NPuzzle::Model
