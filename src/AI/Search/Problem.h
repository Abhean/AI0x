/*
 * Problem.h
 *
 *  Created on: Nov 29, 2011
 *      Author: kique
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_

//============================
// Forward Declarations
//============================
namespace AI
{
	namespace Model
	{
		class IWorld;
		class IState;
		class ICondition;
	}
}

//============================
// CProblem
//============================
namespace AI { namespace Search {

class CProblem
{
public:
			 CProblem();
	virtual ~CProblem();

private:

	// @NOTE[egarcia]: Available actions ¿from World model definition?
	AI::Model::IWorld* 	   m_pWorld;

	AI::Model::IState* 	   m_pInitState;
	AI::Model::ICondition* m_pGoalTest;
};

} } /* namespace AI::Search */
#endif /* PROBLEM_H_ */
