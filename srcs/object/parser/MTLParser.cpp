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

			new_mat.name = mat_name;
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
		}
	}
}

MTLParser::~MTLParser()
{
}

Color	MTLParser::parse_ambient(const char *line) const
{
	float	r, g, b;
	Color	color;

	int	scan_ret = sscanf(line, "Ka %f %f %f", &r, &g, &b);
	if (scan_ret != 0)
		color = (Color){r, g, b};
	else
		std::cerr << "Error while reading an ambient color" << std::endl; // Create class Exception
	return color;
}

Color	MTLParser::parse_diffuse(const char *line) const
{
	float	r, g, b;
	Color	color;

	int	scan_ret = sscanf(line, "Kd %f %f %f", &r, &g, &b);
	if (scan_ret != 0)
		color = (Color){r, g, b};
	else
		std::cerr << "Error while reading diffuse color" << std::endl; // Create class Exception
	return color;
}

Color	MTLParser::parse_specular_color(const char *line) const
{
	float	r, g, b;
	Color	color;

	int	scan_ret = sscanf(line, "Ks %f %f %f", &r, &g, &b);
	if (scan_ret != 0)
		color = (Color){r, g, b};
	else
		std::cerr << "Error while reading specular color" << std::endl; // Create class Exception
	return color;
}

float	MTLParser::parse_specular_index(const char *line) const
{
	float	x;

	int	scan_ret = sscanf(line, "Ns %f", &x);
	if (scan_ret == 0)
		std::cerr << "Error while reading specular index" << std::endl; // Create class Exception
	return x;
}

float	MTLParser::parse_transparency(const char *line) const
{
	float	x;

	int	scan_ret = sscanf(line, "Tr %f", &x);
	if (scan_ret == 0)
		std::cerr << "Error while reading transparency" << std::endl; // Create class Exception
	return x;
}

float	MTLParser::parse_refraction_index(const char *line) const
{
	float	x;

	int	scan_ret = sscanf(line, "Ni %f", &x);
	if (scan_ret == 0)
		std::cerr << "Error while reading specular index" << std::endl; // Create class Exception
	return x;
}
