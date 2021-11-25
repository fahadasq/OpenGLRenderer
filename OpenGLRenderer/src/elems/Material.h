#pragma once

#include "Shader.h"

class Material
{
private:
	std::unique_ptr<Shader> m_Shader;

	void ParseShaderForUniforms(const char* shaderFile);

public:
	Material();
	~Material();

	void Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
};

