/*
 * Service.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: kique
 */

#include "Logger/Logger.h"
#include "Service.h"
#include <GL/glew.h>
#include <GL/glfw.h>

namespace Render
{


int CService::OpenWindow()
{
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
	    fprintf( stderr, "Failed to open GLFW window\n" );
	    glfwTerminate();
	    return -1;
	}
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    return -1;
	}

	glfwSetWindowTitle("Tutorial 01");
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	return 0;
}

void CService::DrawLine(const V3f & _v3Begin, const V3f & _v3End)
{
	// An array of 3 vectors which represents 3 vertices
	GLfloat const g_vertex_buffer_data[] = {
	   _v3Begin.get<0>(), _v3Begin.get<1>(), _v3Begin.get<2>(),
	   _v3End.get<0>(),   _v3End.get<1>(),   _v3End.get<2>()
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	m_vectTempBuffers.push_back(vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_LINES, 0, 2); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

	// Delete
}

void CService::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

}

void CService::EndScene()
{
	// Clean temporal vector buffers
	glDeleteBuffers(m_vectTempBuffers.size(), m_vectTempBuffers.data());
	m_vectTempBuffers.clear();

	// Swap buffers
    glfwSwapBuffers();
}

} /* namespace Render */
