/*
 * IWorld.h
 *
 *  Created on: Oct 22, 2011
 *      Author: kique
 */

#ifndef NPUZZLE_MODEL_STATE_H_
#define NPUZZLE_MODEL_STATE_H_

#include "NPuzzle/Model/Types.h"
#include "AI/Model/State.h"
#include <boost/serialization/vector.hpp>
#include <vector>


namespace NPuzzle { namespace Model {

// Forward Declarations
class CWorld;

// IState
class CState: public AI::Model::IState
{
public:

	 	 	 CState(CWorld const* _pWorld);
	virtual ~CState();

	CWorld const* GetWorld		  () const { return m_pWorld; }
	V2i const& 	  GetEmptySpacePos() const { return m_v2EmptySpacePos; }

private:


	//void InitializeGrid();
	CWorld const*	 m_pWorld;

	V2i 			 m_v2EmptySpacePos;
	std::vector<int> m_vGrid;


	//====================================
	// Serialization
	//====================================
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & _Archive, const unsigned int _uVersion)
	{
		_Archive & boost::serialization::make_nvp("Grid", m_vGrid);
	}
};

} } // namespace NPuzzle::Model

#endif /* NPUZZLE_MODEL_STATE_H_ */
