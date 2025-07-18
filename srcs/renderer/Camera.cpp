#include <Camera.hpp>

Camera::Camera(void)
{
	this->_position = glm::vec3(0.0f, 0.0f, 10.0f);
	this->_front = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - this->_position);
	this->_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->_right = glm::normalize(glm::cross(_up, _front));
}

Camera::~Camera()
{
}

void Camera::processScroll(float yoffset)
{
	this->_position -= this->_front * yoffset * ZOOM_SPEED;
	this->_front = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - this->_position);
	this->_right = glm::normalize(glm::cross(this->_up, this->_front));
}
