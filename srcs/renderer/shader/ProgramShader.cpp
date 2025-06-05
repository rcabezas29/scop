#include <ProgramShader.hpp>

ProgramShader::ProgramShader(void)
{
	Shader	vertShader(SHADER_VERTEX, GL_VERTEX_SHADER), fragShader(SHADER_FRAGMENT, GL_FRAGMENT_SHADER);
	char	infoLog[512];
	int		success;

	this->_id = glCreateProgram();
	glAttachShader(this->_id, vertShader.getShader());
	glAttachShader(this->_id, fragShader.getShader());
	glLinkProgram(this->_id);
	// print linking errors if any
	glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(this->_id, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertShader.getShader());
	glDeleteShader(fragShader.getShader());
}

void	ProgramShader::use(void) const
{
	glUseProgram(this->_id);
}

void	ProgramShader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->_id, name.c_str()), (int)value);
}

void	ProgramShader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->_id, name.c_str()), value);
}

void	ProgramShader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(this->_id, name.c_str()), value);
}

GLuint	ProgramShader::getID(void) const
{
	return this->_id;
}
