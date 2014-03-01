/*
 * Node.h
 *
 *  Created on: Nov 29, 2011
 *      Author: kique
 */

#ifndef NODE_H_
#define NODE_H_

//============================
// Forward Declarations
//============================
namespace AI
{
	namespace Model
	{
		class IState;
		class IAction;
	}
}

//============================
// CNode
//============================
namespace AI { namespace Search {

// @TODO[egarcia]: Templatize over IState?
class CNode
{
public:
			 CNode(AI::Model::IState const* const _pState);
	virtual ~CNode();


private:

	/// World State
	AI::Model::IState const* const m_pState;

	/// Parent Node
	CNode* m_pParent;

	/// Action applied to get this node from parent
	AI::Model::IAction const* m_pAction;
};

} } /* namespace AI::Search */

#endif /* NODE_H_ */
