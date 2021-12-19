#pragma once

#include "Material.h"

class MaterialInstance
{
private:
	std::shared_ptr<Material> m_MaterialType;

public:

	char* m_UniformBuffer;

	MaterialInstance();
	MaterialInstance(const char* filePath);
	~MaterialInstance();

	void Generate(const char* filePath);

	void Bind();

	void SetUniformBindingPoint(const char* name, const unsigned int index);
	void SetUniforms();
	void SetUniformValue(Uniform uniform, void* data);

	void SetMaterialAsset(const char* filePath);
	void SetShaderAsset(const char* vShader, const char* fShader, const char* gShader = nullptr);

	void SerializeMaterial(const char* filePath);

	std::shared_ptr<Material>& GetMaterialType() { return m_MaterialType; }
};

