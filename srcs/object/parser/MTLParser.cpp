#include "MTLParser.hpp"

MTLParser::MTLParser(const std::string file_path)
{
	std::fstream	mtl_file(file_path);
	std::string		line;

	while (std::getline(mtl_file, line))
	{
		if (!strncmp("newmtl ", line.c_str(), 7))
		{
			std::string	mat_name = line.substr(line.find(' ') + 1);
			Material	new_mat;

			while (std::getline(mtl_file, line) && strncmp("newmtl ", line.c_str(), 7))
			{
				if (!strncmp("Ka ", line.c_str(), 3))
					new_mat.ambient_color = this->parse_ambient(line.c_str());
				else if (!strncmp("Kd ", line.c_str(), 3))
					new_mat.diffuse_color = this->parse_diffuse(line.c_str());
				else if (!strncmp("Ks ", line.c_str(), 3))
					new_mat.specular_color = this->parse_specular_color(line.c_str());
				else if (!strncmp("Ns ", line.c_str(), 3))
					new_mat.specular_exponent = this->parse_specular_index(line.c_str());
				else if (!strncmp("d ", line.c_str(), 2) || !strncmp("Tr ", line.c_str(), 3))
					new_mat.transparency = this->parse_transparency(line.c_str());
				else if (!strncmp("Ni ", line.c_str(), 3))
					new_mat.refraction_index = this->parse_refraction_index(line.c_str());
			}
			this->_materials.insert(std::make_pair(mat_name, new_mat));
		}
	}
}

MTLParser::~MTLParser() {}

Color	MTLParser::parse_ambient(const char *line) const
{
	float	r, g, b;
	Color	color;

	int	scan_ret = sscanf(line, "Ka %f %f %f", &r, &g, &b);
	if (scan_ret == 3)
		color = (Color){r, g, b};
	else
		throw ParsingMTLException("Error while reading an ambient color");
	return color;
}

Color	MTLParser::parse_diffuse(const char *line) const
{
	float	r, g, b;
	Color	color;

	int	scan_ret = sscanf(line, "Kd %f %f %f", &r, &g, &b);
	if (scan_ret == 3)
		color = (Color){r, g, b};
	else
		throw ParsingMTLException("Error while reading an diffuse color");
	return color;
}

Color	MTLParser::parse_specular_color(const char *line) const
{
	float	r, g, b;
	Color	color;

	int	scan_ret = sscanf(line, "Ks %f %f %f", &r, &g, &b);
	if (scan_ret == 3)
		color = (Color){r, g, b};
	else
		throw ParsingMTLException("Error while reading an specular color");
	return color;
}

float	MTLParser::parse_specular_index(const char *line) const
{
	float	x;

	int	scan_ret = sscanf(line, "Ns %f", &x);
	if (scan_ret != 1)
		throw ParsingMTLException("Error while reading specular index");
	return x;
}

float	MTLParser::parse_transparency(const char *line) const
{
	float	x;

	int	scan_ret = sscanf(line, "d %f", &x);
	if (scan_ret != 1)
		throw ParsingMTLException("Error while reading transparency");
	return x;
}

float	MTLParser::parse_refraction_index(const char *line) const
{
	float	x;

	int	scan_ret = sscanf(line, "Ni %f", &x);
	if (scan_ret != 1)
		throw ParsingMTLException("Error while reading specular index");
	return x;
}
