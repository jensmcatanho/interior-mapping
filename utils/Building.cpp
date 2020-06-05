/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2020 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "utils/Building.h"
#include "utils/utils.h"

#include <glm/gtc/type_ptr.hpp>

namespace utils {

Building::Building(glm::vec3 position, GLfloat width, GLfloat height, GLfloat depth) :
	Mesh(position),
	width(width),
	height(height),
	depth(depth) {
	
	GenerateData();
}

void Building::GenerateData() {
	GLuint vertices_count = 8;
	GLuint texcoords_count = 8;
	m_NumIndices = 36;
	m_Data.resize(vertices_count * 3 + texcoords_count * 2);
	m_Indices.resize(m_NumIndices);

	std::vector<GLfloat>::iterator d_iterator = m_Data.begin();
	
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f; *d_iterator++ =  0.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = width; *d_iterator++ = 0.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = 1.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = width; *d_iterator++ = height; *d_iterator++ = 0.0f;
	*d_iterator++ = 1.0f; *d_iterator++ = 1.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = height; *d_iterator++ = 0.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 1.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f; *d_iterator++ = -depth;
	*d_iterator++ = 0.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = width; *d_iterator++ = 0.0f; *d_iterator++ = -depth;
	*d_iterator++ = 1.0f; *d_iterator++ = 0.0f;
	*d_iterator++ = width; *d_iterator++ = height; *d_iterator++ = -depth;
	*d_iterator++ = 1.0f; *d_iterator++ = 1.0f;
	*d_iterator++ = 0.0f; *d_iterator++ = height; *d_iterator++ = -depth;
	*d_iterator++ = 0.0f; *d_iterator++ = 1.0f;

	std::vector<GLushort>::iterator i_iterator = m_Indices.begin();

	// Front face
	*i_iterator++ = 0; *i_iterator++ = 1; *i_iterator++ = 2;
	*i_iterator++ = 2; *i_iterator++ = 3; *i_iterator++ = 0;
	// Right face
	*i_iterator++ = 1; *i_iterator++ = 5; *i_iterator++ = 6;
	*i_iterator++ = 6; *i_iterator++ = 2; *i_iterator++ = 1;
	// Back face
	*i_iterator++ = 7; *i_iterator++ = 6; *i_iterator++ = 5;
	*i_iterator++ = 5; *i_iterator++ = 4; *i_iterator++ = 7;
	// Left face
	*i_iterator++ = 4; *i_iterator++ = 0; *i_iterator++ = 3;
	*i_iterator++ = 3; *i_iterator++ = 7; *i_iterator++ = 4;
	// Bottom face
	*i_iterator++ = 4; *i_iterator++ = 5; *i_iterator++ = 1;
	*i_iterator++ = 1; *i_iterator++ = 0; *i_iterator++ = 4;
	// Top face
	*i_iterator++ = 3; *i_iterator++ = 2; *i_iterator++ = 6;
	*i_iterator++ = 6; *i_iterator++ = 7; *i_iterator++ = 3;
}


void Building::Draw(std::shared_ptr<Camera> camera) const {
	glBindVertexArray(m_VAOHandler);
	glUseProgram(m_ShaderProgram);

	glm::vec3 camera_position = camera->GetPosition();
	glUniform3fv(2, 1, glm::value_ptr(camera_position));

	glm::mat4 model_matrix;
	model_matrix = glm::translate(model_matrix, m_Position);

	glm::mat4 mvp_matrix = camera->ProjectionMatrix() * camera->ViewMatrix() * model_matrix;
	glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(mvp_matrix));

	glUniform1f(4, roomSize);
	glUniform1f(5, height/floors);

	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_SHORT, (void*)0);
}

}