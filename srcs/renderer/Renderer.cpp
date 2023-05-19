#include "Renderer.hpp"

Renderer::Renderer()
{
	if (!glfwInit())
		throw std::runtime_error("Unable to init GLFW");

	if (!(this->window = glfwCreateWindow(640, 480, "Scop", NULL, NULL)))
    {
        glfwTerminate();
        throw std::runtime_error("Unable to init GLFW window");
    }

	glfwMakeContextCurrent(window);
}

Renderer::Renderer(const Renderer &copy)
{
	(void)copy;
}

Renderer	&Renderer::operator=(const Renderer &op)
{
	if (this == &op)
		return *this;
	return *this;
}

Renderer::~Renderer(void)
{

}

void	Renderer::render()
{
	while (!glfwWindowShouldClose(this->window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(this->window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
