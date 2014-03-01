/*
 * Action.h
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#ifndef AI_MODEL_ACTION_H_
#define AI_MODEL_ACTION_H_

namespace AI { namespace Model {

// Forward Declarations
class IState;

// IAction
class IAction
{
public:
			 IAction();
	virtual ~IAction();

	virtual float 	 GetApplicationCost (IState* _pWorldState) const = 0;
	virtual bool 	 CanBeAppliedTo		(IState* _pWorldState) const = 0;

	virtual void	 ApplyTo  	  		(IState* _pWorldState) const = 0;

	void Test() { /* ... */ }

protected:

};

} } // namespace AI::WorldModel



#endif /* AI_ACTION_H_ */
