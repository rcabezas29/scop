#include "Renderer.hpp"

Renderer::Renderer()
{

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
	
}
