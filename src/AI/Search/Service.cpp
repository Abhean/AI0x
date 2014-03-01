/*
 * Service.cpp
 *
 *  Created on: Nov 29, 2011
 *      Author: kique
 */

#include "Service.h"

namespace AI { namespace Search {

// Singleton
CService* CService::s_pInstance = nullptr;


/// Singleton Initialization
void CService::Init()
{
	assert(s_pInstance == nullptr);
	s_pInstance = new CService();
}

/// Singleton Destruction
void CService::Done()
{
	assert(s_pInstance != nullptr);
	delete s_pInstance;
}


CService::CService()
{
	// TODO Auto-generated constructor stub

}

CService::~CService()
{
	// TODO Auto-generated destructor stub
}

} } /* namespace AI::Search */
