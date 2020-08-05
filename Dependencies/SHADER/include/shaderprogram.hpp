#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include<string>
#include<map>
#include<glm.hpp>
class ShaderProgram
{
public:
	unsigned int m_ProgramId;

	ShaderProgram();
	~ShaderProgram();
	
	void attachShader(const char* fileName, unsigned int shaderType);

	void link();

	void use();

	void addUniform(const std::string& name);
	void setFloat(const std::string& name, const float value);
	void setInt(const std::string& name, const int value);
	void setvec3(const std::string& name, const glm::vec3& value);
	void setvec4(const std::string& name, const glm::vec4& value);
	void setmat3(const std::string& name, const glm::mat3* valueptr);
	void setmat4(const std::string& name, const glm::mat4* valueptr);
private:
	std::string getShaderFromFile(const char* fileName);

	std::map<std::string, unsigned int> uniformvar;


	

};
	

#endif