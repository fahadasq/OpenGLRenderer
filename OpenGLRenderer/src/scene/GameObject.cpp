#include "pch.h"
#include "GameObject.h"
#include <ErrorHandler.h>
#include <ResourceManager.h>

GameObject::GameObject()
	: m_UUID(), m_Name("Object")
{
}

GameObject::GameObject(const char* meshFilePath)
	: m_UUID(), m_Name("Object")
{
	SetMesh(meshFilePath);
}

GameObject::GameObject(const char* vFilePath, const char* fFilePath, const char* gFilePath)
	: m_UUID(), m_Name("Object")
{
	SetMaterial(vFilePath, fFilePath, gFilePath);
}

GameObject::GameObject(const char* meshFilePath, const char* vFilePath, const char* fFilePath, const char* gFilePath)
	: m_UUID(), m_Name("Object")
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
	BindUniformBlocks();
}

void GameObject::SetMesh(const char* meshFilePath)
{
	m_Mesh = ResourceManager::GetMesh(meshFilePath);
}

void GameObject::Bind()
{
	m_Material->Bind();
	m_Mesh->Bind();
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
	m_Material->GetMaterialType()->GetShader()->SetMatrix4(name, value);
}

void GameObject::BindUniformBlocks()
{
	m_Material->GetMaterialType()->GetShader()->BindUniformBlocks();
}
