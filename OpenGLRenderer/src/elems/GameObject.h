#pragma once

#include "MaterialInstance.h"
#include "Mesh.h"
#include "Transform.h"

class GameObject
{
private:
public:
	Transform m_Transform;
	std::shared_ptr<Mesh> m_Mesh;
	std::unique_ptr<MaterialInstance> m_Material;
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
	void SetUniformBindingPoint(const char* name, unsigned int index);
};

