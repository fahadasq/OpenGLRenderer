#include "pch.h"
#include "ResourceManager.h"

std::unordered_map<ShaderSpecs, std::weak_ptr<Shader>, hash_fn> ResourceManager::m_Shaders;
std::unordered_map<ShaderSpecs, std::weak_ptr<MaterialUniformLayout>, hash_fn> ResourceManager::m_UniformLayouts;
std::unordered_map<ShaderSpecs, std::weak_ptr<Material>, hash_fn> ResourceManager::m_Materials;
std::unordered_map<std::string, std::weak_ptr<Texture2D>> ResourceManager::m_Textures;
std::unordered_map<std::string, std::weak_ptr<Mesh>> ResourceManager::m_Meshes;

// returns true if the texture at specified filepath exists in memory
bool ResourceManager::CheckTextureExists(const char* filePath)
{
	return !m_Textures[filePath].expired();
}

bool ResourceManager::CheckMeshExists(const char* filePath)
{
	return !m_Meshes[filePath].expired();
}

// returns true if a shader program composed from shaders at the specified filepaths exists in memory
bool ResourceManager::CheckShaderExists(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	return !m_Shaders[{ vShaderFile, fShaderFile, gShaderFile }].expired();
}

// returns true if a shader program composed from shaders at the specified filepaths exists in memory
bool ResourceManager::CheckShaderExists(ShaderSpecs specs)
{
	return !m_Shaders[specs].expired();
}

std::shared_ptr<Shader> ResourceManager::GetShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	ShaderSpecs specs(vShaderFile, fShaderFile, gShaderFile);
	if (m_Shaders.find(specs) != m_Shaders.end())
	{
		if (!m_Shaders[specs].expired())
		{
			return m_Shaders[specs].lock();
		}
	}

	
	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->LoadShader(vShaderFile, fShaderFile, gShaderFile);
	m_Shaders[specs] = shader;
	return shader;
}

std::shared_ptr<Shader> ResourceManager::GetShader(ShaderSpecs specs)
{
	if (m_Shaders.find(specs) != m_Shaders.end() && !m_Shaders[specs].expired())
	{
		return m_Shaders[specs].lock();
	}

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->LoadShader(specs.vShaderFile, specs.vShaderFile, specs.gShaderFile);
	m_Shaders[specs] = shader;
	return shader;
}

std::shared_ptr<MaterialUniformLayout> ResourceManager::GetUniformLayout(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	ShaderSpecs specs(vShaderFile, fShaderFile, gShaderFile);
	if (m_UniformLayouts.find(specs) != m_UniformLayouts.end())
	{
		if (!m_UniformLayouts[specs].expired())
		{
			return m_UniformLayouts[specs].lock();
		}
	}


	std::shared_ptr<Shader> shader = ResourceManager::GetShader(vShaderFile, fShaderFile, gShaderFile);
	std::shared_ptr<MaterialUniformLayout> uniformLayout = std::make_shared<MaterialUniformLayout>();
	MaterialUniformLayout shaderLayout = shader->GetMaterialUniforms();
	uniformLayout->uniforms = shaderLayout.uniforms;
	uniformLayout->texUniforms = shaderLayout.texUniforms;
	m_UniformLayouts[specs] = uniformLayout;
	return uniformLayout;
}

std::shared_ptr<MaterialUniformLayout> ResourceManager::GetUniformLayout(ShaderSpecs specs)
{
	if (m_UniformLayouts.find(specs) != m_UniformLayouts.end())
	{
		if (!m_UniformLayouts[specs].expired())
		{
			return m_UniformLayouts[specs].lock();
		}
	}


	std::shared_ptr<Shader> shader = ResourceManager::GetShader(specs);
	std::shared_ptr<MaterialUniformLayout> uniformLayout = std::make_shared<MaterialUniformLayout>();
	MaterialUniformLayout shaderLayout = shader->GetMaterialUniforms();
	uniformLayout->uniforms = shaderLayout.uniforms;
	uniformLayout->texUniforms = shaderLayout.texUniforms;
	m_UniformLayouts[specs] = uniformLayout;
	return uniformLayout;
}

std::shared_ptr<Material> ResourceManager::GetMaterial(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	ShaderSpecs specs(vShaderFile, fShaderFile, gShaderFile);
	if (m_Materials.find(specs) != m_Materials.end())
	{
		if (!m_Materials[specs].expired())
		{
			return m_Materials[specs].lock();
		}
	}


	std::shared_ptr<Material> material = std::make_shared<Material>(vShaderFile, fShaderFile, gShaderFile);
	m_Materials[specs] = material;
	return material;
}

std::shared_ptr<Material> ResourceManager::GetMaterial(ShaderSpecs specs)
{
	if (m_Materials.find(specs) != m_Materials.end())
	{
		if (!m_Materials[specs].expired())
		{
			return m_Materials[specs].lock();
		}
	}


	std::shared_ptr<Material> material = std::make_shared<Material>(specs.vShaderFile, specs.fShaderFile, specs.gShaderFile);
	m_Materials[specs] = material;
	return material;
}

std::shared_ptr<Texture2D> ResourceManager::GetTexture(const char* filePath)
{
	if (m_Textures.find(filePath) != m_Textures.end() && !m_Textures[filePath].expired())
	{
		return m_Textures[filePath].lock();
	}

	std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
	texture->LoadTextureFromFile(filePath);
	m_Textures[filePath] = texture;
	return texture;
}

std::shared_ptr<Mesh> ResourceManager::GetMesh(const char* filePath)
{
	if (m_Meshes.find(filePath) != m_Meshes.end() && !m_Meshes[filePath].expired())
	{
		return m_Meshes[filePath].lock();
	}

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->Load(filePath);
	m_Meshes[filePath] = mesh;
	return mesh;
}
