#include "Object.hpp"

Object::Object(void) {}

Object::Object(const Object &copy)
{
	this->set_faces(copy.get_faces());
	this->set_vertices(copy.get_vertices());
}

Object	&Object::operator=(const Object &op)
{
	if (this == &op)
		return *this;
	this->set_faces(op.get_faces());
	this->set_vertices(op.get_vertices());
	return *this;
}

Object::~Object(void)
{
	this->_vertices.clear();

	for (std::vector<Face*>::iterator it = this->_faces.begin(); it != this->_faces.end(); ++it)
		delete *it;
	this->_faces.clear();
}

void	Object::set_vertices(const std::vector<Vertex>	&v) {this->_vertices = v; }
void	Object::set_faces(const std::vector<Face*>	&f) { this->_faces = f; }

std::vector<Vertex>	Object::get_vertices(void) const { return this->_vertices; }
std::vector<Face*>	Object::get_faces(void) const { return this->_faces; }
