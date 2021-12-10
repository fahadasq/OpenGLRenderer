#include <pch.h>
#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_Shader->LoadShader(vShaderFile, fShaderFile, gShaderFile);
}
