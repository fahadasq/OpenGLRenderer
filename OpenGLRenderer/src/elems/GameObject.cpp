#include "pch.h"
#include "GameObject.h"
#include <ErrorHandler.h>
#include <ResourceManager.h>

GameObject::GameObject()
{
}

GameObject::GameObject(const char* meshFilePath)
{
	SetMesh(meshFilePath);
}

GameObject::GameObject(const char* vFilePath, const char* fFilePath, const char* gFilePath)
{
	SetMaterial(vFilePath, fFilePath, gFilePath);
}

GameObject::GameObject(const char* meshFilePath, const char* vFilePath, const char* fFilePath, const char* gFilePath)
{
	SetMesh(meshFilePath);
	SetMaterial(vFilePath, fFilePath, gFilePath);
}

GameObject::~GameObject()
{
}

void GameObject::SetMaterial(const char* vFilePath, const char* fFilePath, const char* gFilePath)
{
	m_Material = std::make_unique<MaterialInstance>(vFilePath, fFilePath, gFilePath);
}

void GameObject::SetMesh(const char* meshFilePath)
{
	m_Mesh = ResourceManager::GetMesh(meshFilePath);
}

void GameObject::Bind()
{
	m_Mesh->Bind();
	m_Material->Bind();
}

void GameObject::Render()
{
	Bind();
	m_Transform.Update();
	SetUniform("model", m_Transform.GetModel());
	GLCall(glDrawElements(GL_TRIANGLES, m_Mesh->IndexCount, GL_UNSIGNED_INT, 0));
}

void GameObject::SetUniform(const char* name, const glm::mat4& value)
{
	m_Material->m_MaterialType->m_Shader->SetMatrix4(name, value);
}

void GameObject::SetUniformBindingPoint(const char* name, unsigned int index)
{
	m_Material->SetUniformBindingPoint(name, index);
}
