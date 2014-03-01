/*
 * SlideEmptySpace.cpp
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#include "SlideEmptySpace.h"
#include "NPuzzle/Model/State.h"

namespace NPuzzle { namespace Model {

//---------------------------------------
CSlideEmptySpace::CSlideEmptySpace()
{
	// TODO Auto-generated constructor stub

}

//---------------------------------------
CSlideEmptySpace::~CSlideEmptySpace()
{
	// TODO Auto-generated destructor stub
}


//---------------------------------------
float CSlideEmptySpace::GetApplicationCost(AI::Model::IState* _pWorldState) const
{
	return fCOST;
}


//---------------------------------------
bool CSlideEmptySpace::CanBeAppliedTo(AI::Model::IState* _pWorldState) const
{
	assert(_pWorldState != nullptr);

	// @TODO[egarcia]: Safe Cast
	auto pNPuzzleState = static_cast<CState*>(_pWorldState);
	return pNPuzzleState->GetWorld()->CanSlideTile(pNPuzzleState->GetEmptySpacePos(), m_eDirection);
}

//---------------------------------------
void CSlideEmptySpace::ApplyTo(AI::Model::IState* _pWorldState) const
{
}

} } // namespace NPuzzle::Model
