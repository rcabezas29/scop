#include "Object.hpp"

Object::Object(void)
{
	
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
