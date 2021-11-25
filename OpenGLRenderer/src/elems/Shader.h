#pragma once

#include <pch.h>

class Shader
{
private:
	GLuint m_RendererID;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader() : m_RendererID(0) { }
	Shader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	void Compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr);
	void LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	void Bind() const;

	void    SetFloat(const char* name, float value);
	void    SetInteger(const char* name, int value);
	void    SetVector2f(const char* name, float x, float y);
	void    SetVector2f(const char* name, const glm::vec2& value);
	void    SetVector3f(const char* name, float x, float y, float z);
	void    SetVector3f(const char* name, const glm::vec3& value);
	void    SetVector4f(const char* name, float x, float y, float z, float w);
	void    SetVector4f(const char* name, const glm::vec4& value);
	void    SetMatrix4(const char* name, const glm::mat4& matrix);

private:
	GLint GetUniformLocation(const std::string& name);

	void CheckCompileErrors(GLuint object, std::string type);
};