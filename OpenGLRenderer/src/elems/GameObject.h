#pragma once

#include "Material.h"
#include "Mesh.h"

class GameObject
{
private:
	std::shared_ptr<Material> m_Shader;
	std::shared_ptr<Mesh> m_Mesh;
	glm::vec3 m_Position;
public:
	GameObject();
	GameObject(const char* meshFilePath);
	GameObject(const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	GameObject(const char* meshFilePath, const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	~GameObject();

	void SetShader(const char* vFilePath, const char* fFilePath, const char* gFilePath = nullptr);
	void SetMesh(const char* meshFilePath);
};

