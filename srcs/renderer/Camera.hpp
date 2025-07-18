#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define ZOOM_SPEED 0.5f

class Camera
{
	private:
		glm::vec3 _position;
		glm::vec3 _front;
		glm::vec3 _up;
		glm::vec3 _right;

	public:
		Camera();
		~Camera();

		const glm::vec3 &getPosition() const { return this->_position; }
		const glm::vec3 &getFront() const { return this->_front; }
		const glm::vec3 &getUp() const { return this->_up; }
		const glm::vec3 &getRight() const { return this->_right; }

		void setPosition(const glm::vec3 &position) { this->_position = position; }
		void setFront(const glm::vec3 &front) { this->_front = front; }
		void setUp(const glm::vec3 &up) { this->_up = up; }
		void setRight(const glm::vec3 &right) { this->_right = right; }

		glm::mat4 getViewMatrix() const
		{
			return glm::lookAt(this->_position, this->_position + this->_front, this->_up);
		}

		void	processScroll(float yoffset);
};

