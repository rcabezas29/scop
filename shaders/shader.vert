#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;
flat out int isTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int aIsTexture;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	Color = vec3(aColor);
	isTexture = aIsTexture;
}