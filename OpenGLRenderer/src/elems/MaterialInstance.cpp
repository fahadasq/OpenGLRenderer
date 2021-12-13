#include "pch.h"
#include "MaterialInstance.h"
#include <ResourceManager.h>

MaterialInstance::MaterialInstance(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_MaterialType = ResourceManager::GetMaterial(vShaderFile, fShaderFile, gShaderFile);
	m_UniformBuffer = new char[m_MaterialType->m_BufferSize];
	for (Uniform i : m_MaterialType->m_UniformLayout->uniforms)
	{
		Uniform::SetDefaultValue(&m_UniformBuffer[i.offset], i.type);
	}
}

MaterialInstance::~MaterialInstance()
{
	delete[] m_UniformBuffer;
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
	for (unsigned int i = 0; i < m_MaterialType->m_UniformLayout->texUniforms.size(); i++)
	{
		m_MaterialType->m_UniformLayout->texUniforms[i].Bind();
	}

	for (int i = 0; i < m_MaterialType->m_UniformLayout->uniforms.size(); i++)
	{
		Uniform uni = m_MaterialType->m_UniformLayout->uniforms[i];
		SetUniformValue(uni, &m_UniformBuffer[uni.offset]);
	}

}

void MaterialInstance::SetUniformValue(Uniform uniform, void* data)
{
	switch (uniform.type)
	{
	case GL_FLOAT:
		m_MaterialType->m_Shader->SetFloat(uniform.name.c_str(), *((float*)data));
		break;
	case GL_FLOAT_VEC2:
		m_MaterialType->m_Shader->SetVector2f(uniform.name.c_str(), *((glm::vec2*)data));
		break;
	case GL_FLOAT_VEC3:
		m_MaterialType->m_Shader->SetVector3f(uniform.name.c_str(), *((glm::vec3*)data));
		break;
	case GL_FLOAT_VEC4:
		m_MaterialType->m_Shader->SetVector4f(uniform.name.c_str(), *((glm::vec4*)data));
		break;
	case GL_FLOAT_MAT4:
		m_MaterialType->m_Shader->SetMatrix4(uniform.name.c_str(), *((glm::mat4*)data));
		break;
	case GL_INT:
		m_MaterialType->m_Shader->SetInteger(uniform.name.c_str(), *((int*)data));
		break;
	}
}
