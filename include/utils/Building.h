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
#ifndef BUILDING_H
#define BUILDING_H

#include "Mesh.h"

namespace utils {

class Building : public Mesh {
	public:
		Building(glm::vec3 position, GLfloat height, GLfloat width, GLfloat depth);

		virtual void Draw(std::shared_ptr<Camera> scene_camera) const override;

		void SetFloors(GLuint floors);

		void SetRoomSize(GLfloat room_size);

	private:
		void GenerateData();

		GLfloat height;

		GLfloat width;
		
		GLfloat depth;

		GLuint floors;

		GLfloat roomSize;
};

inline void Building::SetFloors(GLuint floors) {
	this->floors = floors;
}

inline void Building::SetRoomSize(GLfloat room_size) {
	roomSize = room_size;
}

}

#endif