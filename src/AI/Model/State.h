/*
 * WorldState.h
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#ifndef AI_MODEL_STATE_H_
#define AI_MODEL_STATE_H_

#include "World.h"

namespace AI { namespace Model {

// Forward Declarations
class IWorld;

// IState
class IState
{
public:
			 IState();
	virtual ~IState();

};

} } // namespace AI::Model

#endif /* AI_MODEL_STATE_H_ */
