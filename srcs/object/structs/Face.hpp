#pragma once

#include <vector>
#include "Vertex.hpp"
#include "Material.hpp"

struct Face
{
	Vertex		vertices[3];
	Vertex		normals[3];
	Vertex		textures[3];
	Material	material;
};