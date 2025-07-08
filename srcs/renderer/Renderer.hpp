#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Object.hpp>
#include <ProgramShader.hpp>
#include <Texture.hpp>

#define TEXTURE_PATH "/tmp/scop/textures/wall.jpg"

class Renderer
{
	private:
		GLFWwindow	*_window;
		bool		_useTexture;

	public:
		Renderer();
		Renderer(const Renderer &copy);
		Renderer	&operator=(const Renderer &op);
		~Renderer(void);

		void	render(const Object &obj);
		void	processInput(GLFWwindow *window);
};
