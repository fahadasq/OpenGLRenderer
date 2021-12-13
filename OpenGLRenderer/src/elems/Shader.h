#pragma once

#include <pch.h>
#include "Texture2D.h"

struct Uniform
{
public:

	GLenum type;
	std::string name;
	unsigned int size;
	unsigned int offset;

	Uniform(GLenum type, std::string name) : type(type), name(name) 
	{
		size = Uniform::GetSizeOfType(type);
		offset = 0;
	}


	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(float);
		case GL_FLOAT_VEC2:
			return sizeof(glm::vec2);
		case GL_FLOAT_VEC3:
			return sizeof(glm::vec3);
		case GL_FLOAT_VEC4:
			return sizeof(glm::vec4);
		case GL_FLOAT_MAT2:
			return sizeof(glm::mat2);
		case GL_FLOAT_MAT3:
			return sizeof(glm::mat3);
		case GL_FLOAT_MAT4:
			return sizeof(glm::mat4);
		case GL_SAMPLER_2D:
			return sizeof(int);
		case GL_INT:
			return sizeof(int);
		}

		return 0;
	}

	static void SetDefaultValue(void* buffer, unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
		{
			float floatValue = 1.0f;
			memcpy(buffer, &floatValue, sizeof(float));
		}
			break;
		case GL_FLOAT_VEC2:
		{
			glm::vec2 vec2Value(1.0f);
			memcpy(buffer, &vec2Value, sizeof(glm::vec2));
		}
			break;
		case GL_FLOAT_VEC3:
		{
			glm::vec3 vec3Value(1.0f);
			memcpy(buffer, &vec3Value, sizeof(glm::vec3));
		}
			break;
		case GL_FLOAT_VEC4:
		{
			glm::vec4 vec4Value(1.0f);
			memcpy(buffer, &vec4Value, sizeof(glm::vec4));
		}	break;

		case GL_FLOAT_MAT2:
		{
			glm::mat2 mat2Value(1.0f);
			memcpy(buffer, &mat2Value, sizeof(glm::mat2));
		}	break;

		case GL_FLOAT_MAT3:
		{
			glm::mat3 mat3Value(1.0f);
			memcpy(buffer, &mat3Value, sizeof(glm::mat3));
		}	break;

		case GL_FLOAT_MAT4:
		{
			glm::mat4 mat4Value(1.0f);
			memcpy(buffer, &mat4Value, sizeof(glm::mat4));
		}	break;
		case GL_INT:
		{
			int intValue = 1;
			memcpy(buffer, &intValue, sizeof(int));
		}	break;

		}
	}
};

struct TextureUniform
{
public:
	unsigned int slot;
	std::string name;
	std::shared_ptr<Texture2D> texture;

	TextureUniform() : slot(0), name(""), texture(nullptr) { }
	TextureUniform(unsigned int slot, const char* name) : slot(slot), name(name) { texture = std::make_shared<Texture2D>(); }

	void Bind() const { texture->Bind(slot); }
};

struct MaterialUniformLayout
{
	std::vector<Uniform> uniforms;
	std::vector<TextureUniform> texUniforms;
};

class Shader
{
private:
	GLuint m_RendererID;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader() : m_RendererID(0) { }
	Shader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~Shader();
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
	void	SetUniformBindingPoint(const char* name, const unsigned int index);
	void	BindUniformBlocks();
	MaterialUniformLayout GetMaterialUniforms();

private:
	GLint GetUniformLocation(const std::string& name);

	void CheckCompileErrors(GLuint object, std::string type);
};