#include "pch.h"
#include "ResourceManager.h"

std::unordered_map<ShaderSpecs, std::weak_ptr<Shader>, hash_fn> ResourceManager::m_Shaders;
std::unordered_map<std::string, std::weak_ptr<Texture2D>> ResourceManager::m_Textures;

// returns true if the texture at specified filepath exists in memory
bool ResourceManager::CheckTextureExists(const char* filePath)
{
	return !m_Textures[filePath].expired();
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