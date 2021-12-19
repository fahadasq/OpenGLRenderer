#include "pch.h"
#include "MaterialInstance.h"
#include <ResourceManager.h>

MaterialInstance::MaterialInstance()
{
	m_MaterialType = std::make_shared<Material>();
}

MaterialInstance::MaterialInstance(const char* filePath)
{
	m_MaterialType = ResourceManager::GetMaterial(filePath);
	m_UniformBuffer = new char[m_MaterialType->GetBufferSize()];
	for (Uniform i : m_MaterialType->GetUniformLayout().uniforms)
	{
		Uniform::SetDefaultValue(&m_UniformBuffer[i.offset], i.type);
	}
}

MaterialInstance::~MaterialInstance()
{
	delete[] m_UniformBuffer;
}

void MaterialInstance::Generate(const char* filePath)
{
	m_MaterialType = ResourceManager::GetMaterial(filePath);
	m_UniformBuffer = new char[m_MaterialType->GetBufferSize()];
	for (Uniform i : m_MaterialType->GetUniformLayout().uniforms)
	{
		Uniform::SetDefaultValue(&m_UniformBuffer[i.offset], i.type);
	}
}

void MaterialInstance::Bind()
{
	m_MaterialType->Bind();
	SetUniforms();
}

void MaterialInstance::SetUniformBindingPoint(const char* name, const unsigned int index)
{
	m_MaterialType->SetUniformBindingPoint(name, index);
}

void MaterialInstance::SetUniforms()
{
	MaterialUniformLayout uniformLayout = m_MaterialType->GetUniformLayout();

	for (unsigned int i = 0; i < uniformLayout.texUniforms.size(); i++)
	{
		uniformLayout.texUniforms[i].Bind();
	}

	for (int i = 0; i < uniformLayout.uniforms.size(); i++)
	{
		Uniform uni = uniformLayout.uniforms[i];
		SetUniformValue(uni, &m_UniformBuffer[uni.offset]);
	}

}

void MaterialInstance::SetUniformValue(Uniform uniform, void* data)
{
	std::shared_ptr<Shader> shader = m_MaterialType->GetShader();

	switch (uniform.type)
	{
	case GL_FLOAT:
		shader->SetFloat(uniform.name.c_str(), *((float*)data));
		break;
	case GL_FLOAT_VEC2:
		shader->SetVector2f(uniform.name.c_str(), *((glm::vec2*)data));
		break;
	case GL_FLOAT_VEC3:
		shader->SetVector3f(uniform.name.c_str(), *((glm::vec3*)data));
		break;
	case GL_FLOAT_VEC4:
		shader->SetVector4f(uniform.name.c_str(), *((glm::vec4*)data));
		break;
	case GL_FLOAT_MAT4:
		shader->SetMatrix4(uniform.name.c_str(), *((glm::mat4*)data));
		break;
	case GL_INT:
		shader->SetInteger(uniform.name.c_str(), *((int*)data));
		break;
	}
}

void MaterialInstance::SetMaterialAsset(const char* filePath)
{
	m_MaterialType->SetMaterialAsset(filePath);
}

void MaterialInstance::SerializeMaterial(const char* filePath)
{
	m_MaterialType->Serialize(filePath);
}
