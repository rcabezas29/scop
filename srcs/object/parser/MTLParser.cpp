#include "MTLParser.hpp"

MTLParser::MTLParser(const std::string file_path)
{
	std::fstream	mtl_file(file_path);
	std::string		line;

	while (std::getline(mtl_file, line))
	{
		
	}
}