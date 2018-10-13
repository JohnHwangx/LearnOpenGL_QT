#include "Shader.h"
using namespace std;

Shader::Shader(const char * vertexPath, const char * fragmentPath, const char * geometryPath)
{
	string vertexString = loadShaderCode(vertexPath);
	string fragmentString = loadShaderCode(fragmentPath);

	const char* vertexCode = vertexString.c_str();
	unsigned int vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER, "vertex");
	const char* fragmentCode = fragmentString.c_str();
	unsigned int fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER, "fragment");
	unsigned int geometryShader;
	if (geometryPath != nullptr)
	{
		const char* geometryCode;
		string geometryString = loadShaderCode(geometryPath);
		geometryCode = geometryString.c_str();
		geometryShader = compileShader(geometryCode, GL_GEOMETRY_SHADER, "geometry");
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	if (geometryPath != nullptr)
	{
		glAttachShader(ID, geometryShader);
	}
	glLinkProgram(ID);
	checkCompileError(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryPath != nullptr)
	{
		glDeleteShader(geometryShader);
	}
}

Shader::~Shader()
{
}

std::string Shader::loadShaderCode(const char * path)
{
	ifstream  shaderFile;
	stringstream shaderStream;
	shaderFile.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		shaderFile.open(path);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
	}
	catch (const std::exception&)
	{
		Message->append("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
	}
	return shaderStream.str();
}

unsigned int Shader::compileShader(const char * shaderCode, GLenum type, const std::string & compileType)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	checkCompileError(shader, compileType);
	return shader;
}

void Shader::checkCompileError(GLuint shader, const std::string & type)
{
	GLint success;
	GLchar loginfo[512];
	if (type != "PROGRAM")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, loginfo);
			Message->append("ERROR::SHADER_COMPILATION_ERROR of type:" + type + "\n" + loginfo + "\n-- ---------------------------------------");
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, loginfo);
			Message->append("ERROR::PROGRAM_LINKING_ERROR of type:" + type + "\n" + loginfo + "\n-- ---------------------------------------");
		}
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string & name, const glm::vec2 & value)
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string & name, float x, float y)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string & name, const glm::vec3 & value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string & name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string & name, const glm::vec4 & value)
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string & name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string & name, const glm::mat2 value)
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string & name, const glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string & name, const glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
