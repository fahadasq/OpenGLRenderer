#pragma once

#include "Material.h"

class MaterialInstance
{
private:
public:
	std::shared_ptr<Material> m_Material;

	char* m_UniformBuffer;

	MaterialInstance();
	MaterialInstance(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~MaterialInstance();

	void SetUniforms();
	void SetUniformValue(Uniform uniform, void* data);
};

