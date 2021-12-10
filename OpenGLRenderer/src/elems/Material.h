#pragma once

#include "Shader.h"
#include "Texture2D.h"

class Material
{
private:

public:
	std::shared_ptr<Shader> m_Shader;
	std::unique_ptr<MaterialUniformLayout> m_UniformLayout;
	Material();
	Material(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~Material();

	char* m_UniformBuffer;

	void Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	void SetUniforms();
	void SetUniformValue(Uniform uniform, void* data);
};