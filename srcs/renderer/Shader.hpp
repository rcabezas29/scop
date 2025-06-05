#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define SHADER_DIR "/usr/share/scop/shaders/"
#define SHADER_VERTEX SHADER_DIR "shader.vert"
#define SHADER_FRAGMENT SHADER_DIR "shader.frag"

class Shader
{
	private:
		GLuint _id;

	public:
		Shader(const char* vertexPath, const char* fragmentPath);

		void	use(void) const;
		void	setBool(const std::string &name, bool value) const;
		void	setInt(const std::string &name, int value) const;
		void	setFloat(const std::string &name, float value) const;

		GLuint	getID(void) const;
};
