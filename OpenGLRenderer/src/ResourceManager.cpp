#include "pch.h"
#include "ResourceManager.h"
#include <ErrorHandler.h>

std::unordered_map<uint64_t, Asset> ResourceManager::m_AssetRepository;
std::unordered_map<uint64_t, ShaderAsset> ResourceManager::m_ShaderAssetRepository;

std::unordered_map<uint64_t, std::weak_ptr<Shader>> ResourceManager::m_LoadedShaders;
std::unordered_map<uint64_t, std::weak_ptr<Texture2D>> ResourceManager::m_LoadedTextures;
std::unordered_map<uint64_t, std::weak_ptr<Material>> ResourceManager::m_LoadedMaterials;
std::unordered_map<uint64_t, std::weak_ptr<Mesh>> ResourceManager::m_LoadedMeshes;

std::shared_ptr<Shader> ResourceManager::GetShader(const char* filepath)
{
	uint64_t ID = ShaderAsset::DeserializeID(filepath);

	if (m_ShaderAssetRepository.find(ID) != m_ShaderAssetRepository.end())
	{
		if (m_LoadedShaders.find(ID) != m_LoadedShaders.end() && !m_LoadedShaders[ID].expired())
		{
			return m_LoadedShaders[ID].lock();
		}
		else
		{
			ShaderAsset asset = m_ShaderAssetRepository[ID];
			std::shared_ptr<Shader> shader = std::make_shared<Shader>(asset);
			m_LoadedShaders[ID] = shader;
			return shader;
		}
	}

	ShaderAsset asset;	
	asset.Deserialize(filepath);
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(asset);
	m_LoadedShaders[ID] = shader;
	return shader;
}

std::shared_ptr<Material> ResourceManager::GetMaterial(const char* filepath)
{
	uint64_t ID = Asset::DeserializeID(filepath);

	if (m_AssetRepository.find(ID) != m_AssetRepository.end())
	{
		if (m_LoadedMaterials.find(ID) != m_LoadedMaterials.end() && !m_LoadedMaterials[ID].expired())
		{
			return m_LoadedMaterials[ID].lock();
		}
		else
		{
			Asset asset = m_AssetRepository[ID];
			std::shared_ptr<Material> material = std::make_shared<Material>(asset);
			m_LoadedMaterials[ID] = material;
			return material;
		}
	}

	Asset asset;
	asset.Deserialize(filepath);
	m_AssetRepository[ID] = asset;
	std::shared_ptr<Material> material = std::make_shared<Material>(asset);
	m_LoadedMaterials[ID] = material;
	return material;
}

std::shared_ptr<Texture2D> ResourceManager::GetTexture(const char* filepath)
{
	uint64_t ID = Asset::DeserializeID(filepath);

	if (m_AssetRepository.find(ID) != m_AssetRepository.end())
	{
		if (m_LoadedTextures.find(ID) != m_LoadedTextures.end() && !m_LoadedTextures[ID].expired())
		{
			return m_LoadedTextures[ID].lock();
		}
		else
		{
			Asset asset = m_AssetRepository[ID];
			std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
			texture->LoadTextureFromFile(asset.GetSourcePath().c_str());
			m_LoadedTextures[ID] = texture;
			return texture;
		}
	}

	Asset asset;
	asset.Deserialize(filepath);
	m_AssetRepository[ID] = asset;
	std::string filePath = asset.GetSourcePath();
	std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
	texture->LoadTextureFromFile(filePath.c_str());
	m_LoadedTextures[ID] = texture;
	return texture;
}

std::shared_ptr<Mesh> ResourceManager::GetMesh(const char* filepath)
{
	uint64_t ID = Asset::DeserializeID(filepath);

	if (m_AssetRepository.find(ID) != m_AssetRepository.end())
	{
		if (m_LoadedMeshes.find(ID) != m_LoadedMeshes.end() && !m_LoadedMeshes[ID].expired())
		{
			return m_LoadedMeshes[ID].lock();
		}
		else
		{
			Asset asset = m_AssetRepository[ID];
			std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(asset);
			m_LoadedMeshes[ID] = mesh;
			return mesh;
		}
	}
	
	Asset asset;
	asset.Deserialize(filepath);
	m_AssetRepository[ID] = asset;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(asset);
	m_LoadedMeshes[ID] = mesh;
	return mesh;
}

const Asset ResourceManager::AddAsset(const char* filePath)
{
	Asset asset(filePath);
	uint64_t id = asset.GetID();
	m_AssetRepository[id] = asset;
	return asset;
}

const Asset ResourceManager::AddAsset(Asset asset)
{
	uint64_t id = asset.GetID();
	m_AssetRepository[id] = asset;
	return asset;
}

const Asset ResourceManager::GetAsset(uint64_t ID)
{
	return (m_AssetRepository.find(ID) != m_AssetRepository.end()) ? m_AssetRepository[ID] : Asset();
}

void ResourceManager::SerializeAsset(Asset& asset, const char* filePath)
{
	asset.Serialize(filePath);
}

const ShaderAsset ResourceManager::AddShaderAsset(const char* vFilepath, const char* fFilepath, const char* gFilepath)
{
	ShaderAsset asset(vFilepath, fFilepath, gFilepath);
	uint64_t id = asset.GetID();
	m_ShaderAssetRepository[id] = asset;
	return asset;
}

const ShaderAsset ResourceManager::AddShaderAsset(ShaderAsset asset)
{
	uint64_t id = asset.GetID();
	m_ShaderAssetRepository[id] = asset;
	return asset;
}

const ShaderAsset ResourceManager::GetShaderAsset(uint64_t ID)
{
	return (m_ShaderAssetRepository.find(ID) != m_ShaderAssetRepository.end()) ? m_ShaderAssetRepository[ID] : ShaderAsset();
}

void ResourceManager::SerializeAsset(ShaderAsset& asset, const char* filePath)
{
	asset.Serialize(filePath);
}
