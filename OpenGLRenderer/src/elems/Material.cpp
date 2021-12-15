#include <pch.h>
#include "Material.h"
#include <ResourceManager.h>
#include <yaml-cpp/yaml.h>

Material::Material()
	: m_Shader(nullptr), m_UniformLayout(nullptr), m_BufferSize(0)
{

}

Material::Material(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
	: m_Shader(nullptr), m_UniformLayout(nullptr), m_BufferSize(0)
{
	m_Shader = ResourceManager::GetShader(vShaderFile, fShaderFile, gShaderFile);
	m_UniformLayout = ResourceManager::GetUniformLayout(vShaderFile, fShaderFile, gShaderFile);

	int size = 0;

	for (int i = 0; i < m_UniformLayout->uniforms.size(); i++)
	{
		m_UniformLayout->uniforms[i].offset += size;
		size += m_UniformLayout->uniforms[i].size;
	}

	m_BufferSize = size;
}

Material::~Material()
{
}

void Material::Bind() const
{
	m_Shader->Bind();
}

void Material::SetUniformBindingPoint(const char* name, const unsigned int index)
{
	m_Shader->SetUniformBindingPoint(name, index);
}

void Material::Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_Shader = ResourceManager::GetShader(vShaderFile, fShaderFile, gShaderFile);
	m_UniformLayout = ResourceManager::GetUniformLayout(vShaderFile, fShaderFile, gShaderFile);

	int size = 0;

	for (int i = 0; i < m_UniformLayout->uniforms.size(); i++)
	{
		m_UniformLayout->uniforms[i].offset += size;
		size += m_UniformLayout->uniforms[i].size;
	}

	m_BufferSize = size;
}

