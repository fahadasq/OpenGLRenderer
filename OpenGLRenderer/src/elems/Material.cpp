#include <pch.h>
#include "Material.h"
#include <ResourceManager.h>

Material::Material()
{
}

Material::Material(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_Shader = ResourceManager::GetShader(vShaderFile, fShaderFile, gShaderFile);
	m_UniformLayout = std::make_unique<MaterialUniformLayout>();
	MaterialUniformLayout shaderLayout = m_Shader->GetMaterialUniforms();
	m_UniformLayout->uniforms = shaderLayout.uniforms;
	m_UniformLayout->texUniforms = shaderLayout.texUniforms;
	std::cout << "Size of Layout Vector: " << m_UniformLayout->uniforms.size() << std::endl;

	int size = 0;

	for (int i = 0; i < m_UniformLayout->uniforms.size(); i++)
	{
		m_UniformLayout->uniforms[i].offset += size;
		size += m_UniformLayout->uniforms[i].size;
	}

	m_UniformBuffer = new char[size];
	std::cout << "Size Of Buffer: " << size << std::endl;;

}

Material::~Material()
{
	delete[] m_UniformBuffer;
}

void Material::Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	m_Shader = ResourceManager::GetShader(vShaderFile, fShaderFile, gShaderFile);
	m_UniformLayout = std::make_unique<MaterialUniformLayout>();
	MaterialUniformLayout shaderLayout = m_Shader->GetMaterialUniforms();
	m_UniformLayout->uniforms = shaderLayout.uniforms;
	m_UniformLayout->texUniforms = shaderLayout.texUniforms;
	std::cout << "Size of Layout Vector: " << m_UniformLayout->uniforms.size() << std::endl;

	int size = 0;

	for (int i = 0; i < m_UniformLayout->uniforms.size(); i++)
	{
		m_UniformLayout->uniforms[i].offset += size;
		size += m_UniformLayout->uniforms[i].size;
	}

	m_UniformBuffer = new char[size];
	std::cout << "Size Of Buffer: " << size << std::endl;;

}

void Material::SetUniforms()
{
	for (unsigned int i = 0; i < m_UniformLayout->texUniforms.size(); i++)
	{
		m_UniformLayout->texUniforms[i].Bind();
	}

	for (int i = 0; i < m_UniformLayout->uniforms.size(); i++)
	{		
		Uniform uni = m_UniformLayout->uniforms[i];
		SetUniformValue(uni, &m_UniformBuffer[uni.offset]);
	}

}

void Material::SetUniformValue(Uniform uniform, void* data)
{
	switch (uniform.type)
	{
	case GL_FLOAT:
		m_Shader->SetFloat(uniform.name.c_str(), *((float*)data));
		break;
	case GL_FLOAT_VEC2:
		m_Shader->SetVector2f(uniform.name.c_str(), *((glm::vec2*)data));
		break;
	case GL_FLOAT_VEC3:
		m_Shader->SetVector3f(uniform.name.c_str(), *((glm::vec3*)data));
		break;
	case GL_FLOAT_VEC4:
		m_Shader->SetVector4f(uniform.name.c_str(), *((glm::vec4*)data));
		break;
	case GL_FLOAT_MAT4:
		m_Shader->SetMatrix4(uniform.name.c_str(), *((glm::mat4*)data));
		break;
	case GL_INT:
		m_Shader->SetInteger(uniform.name.c_str(), *((int*)data));
		break;
	}
}
