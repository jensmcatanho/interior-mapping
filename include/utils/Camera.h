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
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace utils {

enum Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;

class Camera {
	public:
		Camera(glm::vec3 position, GLfloat aspect_ratio);

		void ProcessMovement(Movement direction, GLfloat delta_time);

		void ProcessRotation(GLfloat x_offset, GLfloat y_offset);

		void ProcessZoom(GLfloat y_offset);

		void SetPosition(glm::vec3 position);

		glm::mat4 ViewMatrix() const;

		glm::mat4 ProjectionMatrix() const;

		glm::vec3 GetPosition() const;

		GLfloat m_Zoom;

	private:
		void UpdateVectors();

		glm::vec3 m_Position;

		glm::vec3 m_U;

		glm::vec3 m_V;

		glm::vec3 m_W;

		glm::vec3 m_WorldUp;

		GLfloat m_Yaw;

		GLfloat m_Pitch;

		GLfloat m_MovementSpeed;

		GLfloat m_Sensitivity;

		GLfloat m_AspectRatio;
};

inline glm::mat4 Camera::ViewMatrix() const {
	return glm::lookAt(m_Position, m_Position - m_W, m_V);
}

inline glm::mat4 Camera::ProjectionMatrix() const {
	return glm::perspective(static_cast<double>(glm::radians(m_Zoom)), static_cast<double>(m_AspectRatio), 0.0001, 10000.0);
}

inline glm::vec3 Camera::GetPosition() const {
	return m_Position;
}

inline void Camera::SetPosition(glm::vec3 position) {
	m_Position = position;
}

}

#endif