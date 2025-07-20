#pragma once

#include <string>

struct Color
{
	float	r;
	float	g;
	float	b;
};

struct Material
{
	Color		ambient_color;
	Color		diffuse_color;
	Color		specular_color;
	float		specular_exponent;
	float		transparency;
	float		refraction_index;
};
