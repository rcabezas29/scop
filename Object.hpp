#pragma once

#include <iostream>
#include <fstream>
#include <vector>

struct Vec3
{
	float	x;
	float	y;
	float	z;
};

class Object
{
	private:
		std::vector<Vec3>	_vertices;

	public:
		Object(std::string file_path);
		Object(const Object &copy);
		Object	&operator=(const Object &op);
		virtual	~Object(void);
};

