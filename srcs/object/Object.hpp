#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "structs/Face.hpp"

class Object
{
	private:
		std::vector<Vertex>	_vertices;
		std::vector<Face>	_faces;

	public:
		Object(void);
		Object(const Object &copy);
		Object	&operator=(const Object &op);
		virtual	~Object(void);

		void	set_vertices(const std::vector<Vertex>	&v);
		void	set_faces(const std::vector<Face>	&f);
};
