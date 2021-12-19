#include <pch.h>
#include "Material.h"
#include <ResourceManager.h>
#include <yaml-cpp/yaml.h>

Material::Material()
	: m_Shader(nullptr), m_UniformLayout(), m_BufferSize(0)
{
	m_UUID = UniversallyUniqueID();
}

//Material::Material(const char* filePath)
//	: m_Shader(nullptr), m_UniformLayout(), m_BufferSize(0)
//{
//	m_UUID = UniversallyUniqueID();
//	m_SourceFilePath = filePath;
//	ShaderAsset asset = ResourceManager::AddShaderAsset(vShaderFile, fShaderFile, gShaderFile);
//
//	int size = 0;
//
//	for (int i = 0; i < m_UniformLayout.uniforms.size(); i++)
//	{
//		m_UniformLayout.uniforms[i].offset += size;
//		size += m_UniformLayout.uniforms[i].size;
//	}
//
//	m_BufferSize = size;
//}

Material::Material(Asset asset)
{
	m_UUID = asset.GetID();
	m_SourceFilePath = asset.GetSourcePath();
	m_Type = AssetType::Material;
	m_Shader = ResourceManager::GetShader(m_SourceFilePath.c_str());
	m_UniformLayout = m_Shader->GetMaterialUniforms();

	int size = 0;

	for (int i = 0; i < m_UniformLayout.uniforms.size(); i++)
	{
		m_UniformLayout.uniforms[i].offset += size;
		size += m_UniformLayout.uniforms[i].size;
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

void Material::Generate(Asset asset)
{
	m_UUID = asset.GetID();
	m_SourceFilePath = asset.GetSourcePath();
	m_Type = AssetType::Mesh;
	m_Shader = ResourceManager::GetShader(m_SourceFilePath.c_str());
	m_UniformLayout = m_Shader->GetMaterialUniforms();

	int size = 0;

	for (int i = 0; i < m_UniformLayout.uniforms.size(); i++)
	{
		m_UniformLayout.uniforms[i].offset += size;
		size += m_UniformLayout.uniforms[i].size;
	}

	m_BufferSize = size;
}

void Material::SetMaterialAsset(const char* filePath)
{
	m_SourceFilePath = filePath;
}

void Material::Serialize(const char* filePath)
{
	__super::Serialize(filePath);
}

void Material::Deserialize(const char* filePath)
{
	__super::Deserialize(filePath);
}

