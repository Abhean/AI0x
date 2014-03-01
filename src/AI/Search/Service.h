/*
 * Service.h
 *
 *  Created on: Nov 29, 2011
 *      Author: kique
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <cassert>

//============================
// Forward Declarations
//============================
namespace AI
{
	namespace Model
	{
		class IWorld;
	}
}

//============================
// CService
//============================
namespace AI { namespace Search {

/// Search Request
//@TODO[egarcia]: Template + Type erasure?
struct SRequest
{
	// @TODO[egarcia]: Weak Ptr?
	//CProblem* pProblem;

};

typedef unsigned RequestHandle;

/// Centralize world search requests (state caching, async requests, etc.)
/// @REVIEW[egarcia]: should we have different search services for different world models / search algorithms?
/// @TODO[egarcia]: use / examine boost Singleton
class CService
{
public:

	// Initialization / Destruction (Singleton)
	virtual ~CService();

	static void  Init ();
	static void  Done ();

	CService* Instance() { assert(s_pInstance != 0); return s_pInstance; }


	// @NOTE[egarcia]: RequestHandler (by world/search algorithm) to share results, nodes, etc.
	//virtual RequestHandle Request(CProblem* _pProblem);

private:

	// Initialization / Destruction (Singleton)
	 CService();

	 static CService* s_pInstance;

	 // World
	// @TODO[egarcia]: Request queue
};

} } /* namespace AI::Search */
#endif /* SERVICE_H_ */
