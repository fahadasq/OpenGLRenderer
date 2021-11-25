#include <pch.h>
#include "Material.h"

void Material::ParseShaderForUniforms(const char* shaderFile)
{
	std::ifstream stream(shaderFile);
	std::string line;

	while (getline(stream, line))
	{
		if (line.find("uniform") != std::string::npos)
		{
			if (line.find("float") != std::string::npos)
			{
				// add float uniform
			}
			else if (line.find("int") != std::string::npos)
			{
				// add int uniform
			}
			else if (line.find("vec2") != std::string::npos)
			{
				// add vec2 uniform
			}
			else if (line.find("vec3") != std::string::npos)
			{
				// add vec3 uniform
			}
			else if (line.find("vec4") != std::string::npos)
			{
				// add vec4 uniform
			}
			else if (line.find("mat4"))
			{
				// add mat4 uniform
			}
			else if (line.find("sampler2D"))
			{
				// add texture uniform
			}
		}
	}

	
}

Material::Material()
{
	m_Shader = std::make_unique<Shader>();
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
