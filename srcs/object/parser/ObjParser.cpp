#include "ObjParser.hpp"

ObjParser::ObjParser(const std::string file_path)
{
	std::fstream	obj_file(file_path);
	std::string		line;

	while (std::getline(obj_file, line))
	{
		if (!strncmp("v ", line.c_str(), 2))
			this->parse_vertex(line.c_str());
		else if (!strncmp("vt ", line.c_str(), 3))
			this->parse_texture_vertices(line.c_str());
		else if (!strncmp("l ", line.c_str(), 2))
			this->parse_line(line.c_str());
		else if (!strncmp("f ", line.c_str(), 2))
			this->parse_face(line.c_str());
		else if (!strncmp("mtllib ", line.c_str(), 7))
			this->parse_materials_file(line);
	}
}

ObjParser::~ObjParser() {}

void	ObjParser::parse_vertex(const char *line)
{
	float	x, y, z;

	int	scan_ret = sscanf(line, "v %f %f %f", &x, &y, &z);
	if (scan_ret == 3)
		this->_vertices.push_back((Vertex){x, y, z});
	else
		throw ParsingObjectException("Error while reading a vertex");
}

void	ObjParser::parse_texture_vertices(const char *line)
{
	float	x, y, z;

	int	scan_ret = sscanf(line, "vt %f %f %f", &x, &y, &z);
	if (scan_ret == 3)
		this->_texture_vertices.push_back((Vertex){x, y, z});
	else
		throw ParsingObjectException("Error while reading a vertex");
}

void	ObjParser::parse_line(const char *line)
{
	float	x1, y1, z1, x2, y2, z2;

	int	scan_ret = sscanf(line, "v %f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2);
	if (scan_ret == 6)
	{
		std::pair<Vertex, Vertex>	v;
		v.first = (Vertex){x1, y1, z1};
		v.second = (Vertex){x2, y2, z2};
		this->_lines.push_back(v);
	}
	else
		throw ParsingObjectException("Error while reading a line");
}

void	ObjParser::parse_face(const char *line)
{
	int	a, b, c, d;

	int	scan_ret = sscanf(line, "f %i %i %i %i", &a, &b, &c, &d);
	if (scan_ret == 3)
	{
		Face	*new_face = new Face();

		new_face->vertices[0] = this->_vertices[a - 1];
		new_face->vertices[1] = this->_vertices[b - 1];
		new_face->vertices[2] = this->_vertices[c - 1];
		new_face->indices[0] = a;
		new_face->indices[1] = b;
		new_face->indices[2] = c;

		this->_faces.push_back(new_face);
	}
	else if (scan_ret == 4)
	{
		Face	*new_face = new Face();

		new_face->vertices[0] = this->_vertices[a - 1];
		new_face->vertices[1] = this->_vertices[b - 1];
		new_face->vertices[2] = this->_vertices[c - 1];
		new_face->indices[0] = a;
		new_face->indices[1] = b;
		new_face->indices[2] = c;

		this->_faces.push_back(new_face);
		new_face = new Face();
		new_face->vertices[0] = this->_vertices[a - 1];
		new_face->vertices[1] = this->_vertices[c - 1];
		new_face->vertices[2] = this->_vertices[d - 1];
		new_face->indices[0] = a;
		new_face->indices[1] = c;
		new_face->indices[2] = d;

		this->_faces.push_back(new_face);
	}
	else
		throw ParsingObjectException("Error while reading a face");
}

void	ObjParser::parse_materials_file(const std::string line)
{
	MTLParser	mtl_parser(line.substr(line.find(' ') + 1));

}

Object	ObjParser::generate_object() const
{
	Object	object;

	object.set_faces(this->_faces);
	object.set_vertices(this->_vertices);

	return object;   
}
