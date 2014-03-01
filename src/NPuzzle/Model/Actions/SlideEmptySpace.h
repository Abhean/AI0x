/*
 * SlideEmptySpace.h
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#ifndef NPUZZLE_SLIDEEMPTYSPACE_H_
#define NPUZZLE_SLIDEEMPTYSPACE_H_

#include "AI/Model/Action.h"
#include "NPuzzle/Model/World.h"

namespace NPuzzle { namespace Model {

// Forward Declarations
class CState;

// CSlideEmptySpace
class CSlideEmptySpace: public AI::Model::IAction
{
public:

	//====================================
	// Constants
	//====================================
	static constexpr float fCOST = 1.0f;

	//====================================
	// Initialization / Destruction
	//====================================
			 CSlideEmptySpace();
	virtual ~CSlideEmptySpace();

	//====================================
	// IAction
	//====================================
	virtual float 	 GetApplicationCost (AI::Model::IState* _pWorldState) const override;

	virtual bool 	 CanBeAppliedTo     (AI::Model::IState* _pWorldState) const override;
	virtual void	 ApplyTo  	  		  (AI::Model::IState* _pWorldState) const override;

	//====================================
	// CSlideEmptySpace
	//====================================


private:

	CWorld::ESlideDirection m_eDirection;
};

} } // namespace NPuzzle::Model

#endif /* NPUZZLE_SLIDEEMPTYSPACE_H_ */
