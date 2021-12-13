#pragma once

#include "elems/MaterialInstance.h"
#include "elems/Mesh.h"
#include "elems/Transform.h"
#include <UUID.h>

class GameObject
{
private:
	UUID m_UUID;
	Transform m_Transform;
	std::shared_ptr<Mesh> m_Mesh;
	std::unique_ptr<MaterialInstance> m_Material;
	std::string m_Name;

public:
	GameObject();
	GameObject(const char* meshFilePath);
	GameObject(const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	GameObject(const char* meshFilePath, const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	~GameObject();

	void SetMaterial(const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	void SetMesh(const char* meshFilePath);

	void Bind();

	void Render();

	void SetUniform(const char* name, const glm::mat4& value);
	void BindUniformBlocks();

	Transform& GetTransform() { return m_Transform; }
	MaterialInstance* GetMaterial() const { return m_Material.get(); }

	const uint64_t& GetID() const { return m_UUID; }
	const std::shared_ptr<Mesh>& GetMesh() const { return m_Mesh; }
	const std::string& GetName() const { return m_Name; }
};

