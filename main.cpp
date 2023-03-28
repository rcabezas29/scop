#include "Object.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments" << std::endl;
		exit(1);
	}

	Object	*obj = new Object(argv[1]);

	delete obj;
	return 0;
}