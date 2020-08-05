#include"shaderprogram.hpp"
#include<glad/glad.h>
#include<fstream>
#include<iostream>
ShaderProgram::ShaderProgram()
{
	m_ProgramId = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ProgramId);
}
void ShaderProgram::link()
{
	glLinkProgram(m_ProgramId);
}
void ShaderProgram::use()
{
	glUseProgram(m_ProgramId);
}

void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType)
{
	unsigned int shaderId = glCreateShader(shaderType);

	std::string sourceCode = getShaderFromFile(fileName);

	const char* chSourceCode = &sourceCode[0];

	glShaderSource(shaderId, 1, &chSourceCode, 0);

	glCompileShader(shaderId);

	glAttachShader(m_ProgramId, shaderId);

	glDeleteShader(shaderId);

}
std::string ShaderProgram::getShaderFromFile(const char* fileName)
{
	std::ifstream file(fileName);

	std::string data;

	if (file.is_open())
	{

		char readChar;

		while ((readChar = file.get()) != EOF)
		{
			data += readChar;
		}

		file.close();
	}



	return data;


}

void ShaderProgram::addUniform(const std::string& name) {
	uniformvar[name] = glGetUniformLocation(m_ProgramId, name.c_str());
}

void ShaderProgram::setFloat(const std::string& name, const float value)
{
	glUniform1f(uniformvar[name], value);
}
void ShaderProgram::setInt(const std::string& name, const int value)
{
	glUniform1i(uniformvar[name], value);
}
void ShaderProgram::setvec3(const std::string& name,const glm::vec3& value)
{
	glUniform3f(uniformvar[name], value.x,value.y,value.z);
}

void ShaderProgram::setmat3(const std::string& name, const glm::mat3* valueptr)
{
	glUniformMatrix3fv(uniformvar[name],1,false,(GLfloat*)valueptr);
}

void ShaderProgram::setvec4(const std::string& name, const glm::vec4& value)
{
	glUniform4f(uniformvar[name], value.r, value.g, value.b, value.a);
}

void ShaderProgram::setmat4(const std::string& name, const glm::mat4* valueptr)
{
	glUniformMatrix4fv(uniformvar[name], 1, false, (GLfloat*)valueptr);
}