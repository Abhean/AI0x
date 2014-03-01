/*
 * Service.h
 *
 *  Created on: Feb 16, 2012
 *      Author: kique
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include "GL/glew.h"
#include "GL/gl.h"
#include "Foundation/Singleton.h"
#include "Foundation/Types.h"
#include <iostream>

namespace Render
{

class CService : public Foundation::CSingleton<CService>
{
public:

	int  OpenWindow();

	void BeginScene();
	void EndScene();

	void DrawLine(V3f const& _v3Begin, V3f const& _v3End);


private:

	typedef std::vector<GLuint>   TVertexBufferVector;
	TVertexBufferVector::iterator TVertexBufferVectorIt;

	TVertexBufferVector m_vectTempBuffers;
};

} /* namespace Render */
#endif /* SERVICE_H_ */
