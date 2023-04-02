#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "structs/Material.hpp"

class MTLParser
{
	private:
		std::vector<Material>	_materials;

	public:
		MTLParser(const std::string file_path);
		virtual ~MTLParser(void);
};

