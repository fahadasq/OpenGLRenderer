#include <pch.h>
#include "Material.h"

void Material::ParseShaderForUniforms(const char* shaderFile)
{
	std::ifstream stream(shaderFile);
	std::string line;
}

Material::Material()
{
	m_Shader = std::make_unique<Shader>();
}

Material::~Material()
{
}

void Material::Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_Shader->LoadShader(vShaderFile, fShaderFile, gShaderFile);
	ParseShaderForUniforms(vShaderFile);
	ParseShaderForUniforms(fShaderFile);

	if (gShaderFile != nullptr)
	{
		ParseShaderForUniforms(gShaderFile);
	}

}
