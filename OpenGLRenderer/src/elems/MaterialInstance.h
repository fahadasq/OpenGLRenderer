#pragma once

#include "Material.h"

class MaterialInstance
{
private:

public:
	std::shared_ptr<Material> m_MaterialType;

	char* m_UniformBuffer;

	MaterialInstance();
	MaterialInstance(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~MaterialInstance();

	void Bind();

	void SetUniformBindingPoint(const char* name, const unsigned int index);
	void SetUniforms();
	void SetUniformValue(Uniform uniform, void* data);
};

