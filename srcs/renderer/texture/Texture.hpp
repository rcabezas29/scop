#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define TEXTURE_PATH "/tmp/scop/textures/wall.jpg"

class Texture
{
	private:
		unsigned int	_id;
	
	public:
		Texture(void);

		unsigned int get_id(void) const { return this->_id; }
};
