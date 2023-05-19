#include <iostream>
#include "Object.hpp"
#include "ObjParser.hpp"
#include "Renderer.hpp"

Object	create_object_from_parser(const std::string file_path)
{
	ObjParser	parser(file_path);

	return parser.generate_object();
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		exit(1);
	}

	try
	{
		Object obj = create_object_from_parser(argv[1]);

		Renderer	renderer;
		// renderer.render();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}