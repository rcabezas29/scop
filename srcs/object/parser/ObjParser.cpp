#include "ObjParser.hpp"

ObjParser::ObjParser(const std::string file_path)
{
	std::fstream	obj_file(file_path);
	std::string		line;

	while (std::getline(obj_file, line))
	{
		if (!strncmp("v ", line.c_str(), 2))
			this->parse_vertex(line.c_str());
		else if (!strncmp("l ", line.c_str(), 2))
			this->parse_line(line.c_str());
		else if (!strncmp("mtllib ", line.c_str(), 7))
			this->parse_materials_file(line);
	}
}

ObjParser::~ObjParser()
{
	
}

void	ObjParser::parse_vertex(const char *line)
{
	float	x, y, z;

	int	scan_ret = sscanf(line, "v %f %f %f", &x, &y, &z);
	if (scan_ret != 0)
		this->_vertices.push_back((Vertex){x, y, z});
	else
		std::cerr << "Error while reading a vertex" << std::endl; // Create class Exception
}

void	ObjParser::parse_line(const char *line)
{
	float	x1, y1, z1, x2, y2, z2;

	int	scan_ret = sscanf(line, "v %f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2);
	if (scan_ret != 0)
	{
		std::pair<Vertex, Vertex>	v;
		v.first = (Vertex){x1, y1, z1};
		v.second = (Vertex){x2, y2, z2};
		this->_lines.push_back(v);
	}
	else
		std::cerr << "Error while reading a line" << std::endl; // Create class Exception
}

void	ObjParser::parse_materials_file(const std::string line)
{
	MTLParser	mtl_parser(line.substr(line.find(' ') + 1));

}
