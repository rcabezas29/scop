#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>

class ProgramShader
{
	private:
		GLuint _id;

	public:
		ProgramShader(void);
		// ~ProgramShader();

		void	use(void) const;
		void	setBool(const std::string &name, bool value) const;
		void	setInt(const std::string &name, int value) const;
		void	setFloat(const std::string &name, float value) const;

		GLuint	getID(void) const;
};
