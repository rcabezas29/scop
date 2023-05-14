#include <iostream>
#include "Object.hpp"
#include "ObjParser.hpp"

Object	create_object_from_parser(const std::string file_path)
{
	ObjParser	parser(file_path);

	return parser.generate_object();
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments" << std::endl;
		exit(1);
	}

	Object obj = create_object_from_parser(argv[1]);
	return 0;
}