#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include "structs/Face.hpp"
#include "MTLParser.hpp"

class ObjParser
{
	private:
		std::vector<Face>		_faces;
		std::vector<Vertex>		_vertices;
		std::vector<std::pair<Vertex, Vertex> >	_lines;
		std::vector<Material>	_materials;

	public:
		ObjParser(const std::string file);
		virtual ~ObjParser(void);

		void	parse_vertex(const char *line);
		void	parse_line(const char *line);
		void	parse_materials_file(const std::string line);
};
