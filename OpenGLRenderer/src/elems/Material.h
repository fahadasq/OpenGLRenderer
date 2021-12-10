#pragma once

#include "Shader.h"
#include "Texture2D.h"

struct MaterialUniformLayout
{
	std::unique_ptr<std::vector<Uniform>> uniforms;
	
};

class Material
{
private:
	std::shared_ptr<Shader> m_Shader;

public:
	Material();
	~Material();

	void Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
};

