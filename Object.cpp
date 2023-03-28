#include "Object.hpp"

Object::Object(std::string file_path)
{
	std::fstream	obj_file(file_path);
	std::string		line;
	float			x, y, z;

	while (std::getline(obj_file, line))
	{
		sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
		printf("VERTEX: %f %f %f\n", x, y, z);
	}
	
}

Object::Object(const Object &copy)
{
	(void)copy;
}

Object	&Object::operator=(const Object &op)
{
	(void)op;
	return *this;
}

Object::~Object(void)
{
	this->_vertices.clear();
}
