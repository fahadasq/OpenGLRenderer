#pragma once

#include "Shader.h"
#include "Texture2D.h"

class Material
{
private:

public:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<MaterialUniformLayout> m_UniformLayout;
	unsigned int m_BufferSize;

	Material();
	Material(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~Material();


	void Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
};