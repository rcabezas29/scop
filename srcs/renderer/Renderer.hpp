#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

class Renderer
{
	private:
		GLFWwindow* window;

	public:
		Renderer();
		Renderer(const Renderer &copy);
		Renderer	&operator=(const Renderer &op);
		~Renderer(void);

		void	render();
};
