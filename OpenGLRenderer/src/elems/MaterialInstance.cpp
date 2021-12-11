#include "pch.h"
#include "MaterialInstance.h"
#include <ResourceManager.h>

MaterialInstance::MaterialInstance(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_Material = ResourceManager::GetMaterial(vShaderFile, fShaderFile, gShaderFile);
	m_UniformBuffer = new char[m_Material->m_BufferSize];
}

MaterialInstance::~MaterialInstance()
{
	delete[] m_UniformBuffer;
}

void MaterialInstance::SetUniforms()
{
	for (unsigned int i = 0; i < m_Material->m_UniformLayout->texUniforms.size(); i++)
	{
		m_Material->m_UniformLayout->texUniforms[i].Bind();
	}

	for (int i = 0; i < m_Material->m_UniformLayout->uniforms.size(); i++)
	{
		Uniform uni = m_Material->m_UniformLayout->uniforms[i];
		SetUniformValue(uni, &m_UniformBuffer[uni.offset]);
	}

}

void MaterialInstance::SetUniformValue(Uniform uniform, void* data)
{
	switch (uniform.type)
	{
	case GL_FLOAT:
		m_Material->m_Shader->SetFloat(uniform.name.c_str(), *((float*)data));
		break;
	case GL_FLOAT_VEC2:
		m_Material->m_Shader->SetVector2f(uniform.name.c_str(), *((glm::vec2*)data));
		break;
	case GL_FLOAT_VEC3:
		m_Material->m_Shader->SetVector3f(uniform.name.c_str(), *((glm::vec3*)data));
		break;
	case GL_FLOAT_VEC4:
		m_Material->m_Shader->SetVector4f(uniform.name.c_str(), *((glm::vec4*)data));
		break;
	case GL_FLOAT_MAT4:
		m_Material->m_Shader->SetMatrix4(uniform.name.c_str(), *((glm::mat4*)data));
		break;
	case GL_INT:
		m_Material->m_Shader->SetInteger(uniform.name.c_str(), *((int*)data));
		break;
	}
}
