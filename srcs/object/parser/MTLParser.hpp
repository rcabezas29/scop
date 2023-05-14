#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include "structs/Material.hpp"

class MTLParser
{
	private:
		std::vector<Material>	_materials;

	public:
		MTLParser(const std::string file_path);
		virtual ~MTLParser(void);

		Color	parse_ambient(const char *line) const;
		Color	parse_diffuse(const char *line) const;
		Color	parse_specular_color(const char *line) const;
		float	parse_specular_index(const char *line) const;
		float	parse_transparency(const char *line) const;
		float	parse_refraction_index(const char *line) const;
};

