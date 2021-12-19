#pragma once

#include "elems/MaterialInstance.h"
#include "elems/Mesh.h"
#include "elems/Transform.h"
#include <UUID.h>

class GameObject
{
private:
	UniversallyUniqueID m_UUID;
	Transform m_Transform;
	std::shared_ptr<Mesh> m_Mesh;
	std::unique_ptr<MaterialInstance> m_Material;
	std::string m_Name;

public:
	GameObject();
	GameObject(const char* meshFilePath, const char* materialFilePath);
	~GameObject();

	void SetMaterial(const char* filePath);
	void SetMesh(const char* meshFilePath);
	void SetMeshAsset(const char* meshFilePath);
	void SetMaterialAsset(const char* materialFilePath);
	void SetShaderAsset(const char* vShader, const char* fShader, const char* gShader = nullptr);

	void Bind();

	void Render();

	void SetUniform(const char* name, const glm::mat4& value);
	void BindUniformBlocks();

	Transform& GetTransform() { return m_Transform; }
	MaterialInstance* GetMaterial() const { return ((m_Material) ? m_Material.get() : nullptr); }

	void SerializeMesh(const std::string& filepath);
	void SerializeMaterial(const std::string& filepath);

	const uint64_t& GetID() const { return m_UUID; }
	const std::shared_ptr<Mesh>& GetMesh() const { return ((m_Mesh) ? m_Mesh : nullptr); }
	const std::string& GetName() const { return m_Name; }
};

