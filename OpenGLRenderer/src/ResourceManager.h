#pragma once

#include "elems/Texture2D.h"
#include "elems/Material.h"
#include "elems/Mesh.h"

struct ShaderSpecs
{
public:
	const char* vShaderFile;
	const char* fShaderFile;
	const char* gShaderFile;

	ShaderSpecs() { }
	ShaderSpecs(const char* vFile, const char* fFile, const char* gFile = nullptr) : vShaderFile(vFile), fShaderFile(fFile), gShaderFile(gFile) { }

	bool operator==(const ShaderSpecs& o) const {
		return vShaderFile == o.vShaderFile && fShaderFile == o.fShaderFile && ((gShaderFile != nullptr) ? gShaderFile == o.gShaderFile : true);
	}
};

struct hash_fn
{
	std::size_t operator() (const ShaderSpecs& specs) const
	{
		std::size_t h1 = std::hash<const char*>()(specs.vShaderFile);
		std::size_t h2 = std::hash<const char*>()(specs.fShaderFile);
		std::size_t h3 = std::hash<const char*>()(specs.gShaderFile);
		return h1 ^ h2 ^ h3;
	}
};

class ResourceManager
{
public:
	static std::unordered_map<ShaderSpecs, std::weak_ptr<Shader>, hash_fn> m_Shaders;
	static std::unordered_map<ShaderSpecs, std::weak_ptr<MaterialUniformLayout>, hash_fn> m_UniformLayouts;
	static std::unordered_map<ShaderSpecs, std::weak_ptr<Material>, hash_fn> m_Materials;
	static std::unordered_map<std::string, std::weak_ptr<Texture2D>> m_Textures;
	static std::unordered_map<std::string, std::weak_ptr<Mesh>> m_Meshes;

	static bool CheckTextureExists(const char* filePath);
	static bool CheckMeshExists(const char* filePath);
	static bool CheckShaderExists(const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	static bool CheckShaderExists(ShaderSpecs specs);

	static std::shared_ptr<Shader> GetShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static std::shared_ptr<Shader> GetShader(ShaderSpecs specs);

	static std::shared_ptr<MaterialUniformLayout> GetUniformLayout(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static std::shared_ptr<MaterialUniformLayout> GetUniformLayout(ShaderSpecs specs);

	static std::shared_ptr<Material> GetMaterial(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static std::shared_ptr<Material> GetMaterial(ShaderSpecs specs);

	static std::shared_ptr<Texture2D> GetTexture(const char* filePath);
	static std::shared_ptr<Mesh> GetMesh(const char* filePath);

private:
	ResourceManager() { }
};

