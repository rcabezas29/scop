#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define SHADER_DIR "/tmp/scop/shaders/"
#define SHADER_VERTEX SHADER_DIR "shader.vert"
#define SHADER_FRAGMENT SHADER_DIR "shader.frag"

class Shader
{
	private:
		unsigned int _shader;

	public:
		Shader(const char *shaderPath, const GLenum shaderType);

		unsigned int getShader(void) const;
};
