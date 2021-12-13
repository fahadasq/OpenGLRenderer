#pragma once

#include "Material.h"

class MaterialInstance
{
private:
	std::shared_ptr<Material> m_MaterialType;

public:

	char* m_UniformBuffer;

	MaterialInstance();
	MaterialInstance(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~MaterialInstance();

	void Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);

	void Bind();

	void SetUniformBindingPoint(const char* name, const unsigned int index);
	void SetUniforms();
	void SetUniformValue(Uniform uniform, void* data);

	std::shared_ptr<Material>& GetMaterialType() { return m_MaterialType; }
};

