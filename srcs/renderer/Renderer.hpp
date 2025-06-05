#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <Object.hpp>
#include <ProgramShader.hpp>

class Renderer
{
	private:
		GLFWwindow	*_window;

	public:
		Renderer();
		Renderer(const Renderer &copy);
		Renderer	&operator=(const Renderer &op);
		~Renderer(void);

		void	render(const Object &obj);
};
