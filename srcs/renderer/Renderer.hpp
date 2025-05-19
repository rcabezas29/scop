#pragma once

class Renderer
{
	private:

	public:
		Renderer();
		Renderer(const Renderer &copy);
		Renderer	&operator=(const Renderer &op);
		~Renderer(void);

		void	render();
};
