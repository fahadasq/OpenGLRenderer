#pragma once

#include "elems/Texture2D.h"
#include "elems/Material.h"
#include "elems/Mesh.h"
#include "AssetTypes.h"


class ResourceManager
{
public:
	static std::unordered_map<uint64_t, Asset> m_AssetRepository;
	static std::unordered_map<uint64_t, ShaderAsset> m_ShaderAssetRepository;

	static std::unordered_map<uint64_t, std::weak_ptr<Shader>> m_LoadedShaders;
	static std::unordered_map<uint64_t, std::weak_ptr<Mesh>> m_LoadedMeshes;
	static std::unordered_map<uint64_t, std::weak_ptr<Material>> m_LoadedMaterials;
	static std::unordered_map<uint64_t, std::weak_ptr<Texture2D>> m_LoadedTextures;

	static bool CheckAssetExists(uint64_t ID);

	static std::shared_ptr<Shader> GetShader(const char* filepath);
	static std::shared_ptr<Material> GetMaterial(const char* filepath);
	static std::shared_ptr<Texture2D> GetTexture(const char* filepath);
	static std::shared_ptr<Mesh> GetMesh(const char* filepath);

	static const Asset AddAsset(const char* filePath);
	static const Asset AddAsset(Asset asset);
	static const Asset GetAsset(uint64_t ID);

	static void SerializeAsset(Asset& asset, const char* filePath);

	static const ShaderAsset AddShaderAsset(const char* vFilepath, const char* fFilepath, const char* gFilepath = nullptr);
	static const ShaderAsset AddShaderAsset(ShaderAsset asset);
	static const ShaderAsset GetShaderAsset(uint64_t ID);

	static void SerializeAsset(ShaderAsset& asset, const char* filePath);


private:
	ResourceManager() { }
};

