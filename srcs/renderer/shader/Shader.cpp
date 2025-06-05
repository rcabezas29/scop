#include <Shader.hpp>

Shader::Shader(const char* shaderPath, const GLenum shaderType)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string		code;
	std::ifstream	file;
	char			infoLog[512];
	int				success;
	// ensure ifstream objects can throw exceptions:
	file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream	shaderStream;
		// open files
		file.open(shaderPath);
		// read file’s buffer contents into streams
		shaderStream << file.rdbuf();
		// close file handlers
		file.close();
		// convert stream into string
		code = shaderStream.str();
	}
	catch (std::ifstream::failure &e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}
	const char* shaderCode = code.c_str();

	// vertex Shader
	this->_shader = glCreateShader(shaderType);
	glShaderSource(this->_shader, 1, &shaderCode, NULL);
	glCompileShader(this->_shader);
	// print compile errors if any
	glGetShaderiv(this->_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->_shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

unsigned int Shader::getShader(void) const
{
	return this->_shader;
}
