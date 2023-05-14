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

void	Object::set_vertices(const std::vector<Vertex>	&v) {this->_vertices = v; }
void	Object::set_faces(const std::vector<Face>	&f) { this->_faces = f; }

std::vector<Vertex>	Object::get_vertices(void) const { return this->_vertices; }
std::vector<Face>	Object::get_faces(void) const { return this->_faces; }