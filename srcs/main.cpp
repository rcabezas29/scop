#include <iostream>

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments" << std::endl;
		exit(1);
	}

	return 0;
}