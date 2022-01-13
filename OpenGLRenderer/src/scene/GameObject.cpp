#include "pch.h"
#include "GameObject.h"
#include <ErrorHandler.h>
#include <ResourceManager.h>
#include <Stats.h>

GameObject::GameObject()
	: m_UUID(), m_Name("Object")
{

}

GameObject::GameObject(const char* meshFilePath, const char* materialFilePath)
	: m_UUID(), m_Name("Object")
{
	SetMesh(meshFilePath);
	SetMaterial(materialFilePath);
}

GameObject::~GameObject()
{
}

void GameObject::SetMaterial(const char* filePath)
{
	m_Material = std::make_unique<MaterialInstance>(filePath);
	BindUniformBlocks();
}

void GameObject::SetMesh(const char* meshFilePath)
{
	m_Mesh = ResourceManager::GetMesh(meshFilePath);
}

void GameObject::Bind()
{
	if (m_Material)
	m_Material->Bind();
	if (m_Mesh)
	m_Mesh->Bind();
}

void GameObject::Render()
{
	if (m_Material && m_Mesh)
	{
		m_Transform.Update();
		SetUniform("model", m_Transform.GetModel());
		GLCall(glDrawElements(GL_TRIANGLES, m_Mesh->IndexCount, GL_UNSIGNED_INT, 0));
		Stats::AddDrawCalls(1);
	}
}

void GameObject::SetUniform(const char* name, const glm::mat4& value)
{
	m_Material->GetMaterialType()->GetShader()->SetMatrix4(name, value);
}

void GameObject::SetUniform(const char* name, int value)
{
	m_Material->GetMaterialType()->GetShader()->SetInteger(name, value);
}

void GameObject::BindUniformBlocks()
{
	m_Material->GetMaterialType()->GetShader()->BindUniformBlocks();
}