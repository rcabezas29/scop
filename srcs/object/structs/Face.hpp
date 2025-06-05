#pragma once

#include <vector>
#include "Vertex.hpp"
#include "Material.hpp"

struct Face
{
	Vertex		vertices[3];
	Vertex		textures[3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }; // Default initialized to zero
	int			indices[3];
	// Vertex		normals[3];
	// Material	material;
};