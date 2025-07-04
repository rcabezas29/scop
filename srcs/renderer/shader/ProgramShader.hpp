#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>
#include <glm/glm.hpp>

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

		void setVec2(const std::string &name, const glm::vec2 &value) const
		{
			glUniform2fv(glGetUniformLocation(this->_id, name.c_str()), 1, &value[0]);
		}
		void setVec2(const std::string &name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(this->_id, name.c_str()), x, y);
		}
		// ------------------------------------------------------------------------
		void setVec3(const std::string &name, const glm::vec3 &value) const
		{
			glUniform3fv(glGetUniformLocation(this->_id, name.c_str()), 1, &value[0]);
		}
		void setVec3(const std::string &name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(this->_id, name.c_str()), x, y, z);
		}
		// ------------------------------------------------------------------------
		void setVec4(const std::string &name, const glm::vec4 &value) const
		{
			glUniform4fv(glGetUniformLocation(this->_id, name.c_str()), 1, &value[0]);
		}
		void setVec4(const std::string &name, float x, float y, float z, float w) 
		{
			glUniform4f(glGetUniformLocation(this->_id, name.c_str()), x, y, z, w);
		}
		// ------------------------------------------------------------------------
		void setMat2(const std::string &name, const glm::mat2 &mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void setMat3(const std::string &name, const glm::mat3 &mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// ------------------------------------------------------------------------
		void setMat4(const std::string &name, const glm::mat4 &mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		GLuint	getID(void) const;
};
