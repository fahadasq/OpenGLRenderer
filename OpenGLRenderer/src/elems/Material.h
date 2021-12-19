#pragma once

#include <AssetTypes.h>
#include "Shader.h"

#include "Texture2D.h"


class Material : public Asset
{
private:
	std::shared_ptr<Shader> m_Shader;
	MaterialUniformLayout m_UniformLayout;
	unsigned int m_BufferSize;

public:

	Material();
	Material(const char* filePath);
	Material(Asset asset);
	~Material();


	void Bind() const;
	void SetUniformBindingPoint(const char* name, const unsigned int index);
	void Generate(Asset asset);

	MaterialUniformLayout& GetUniformLayout() { return m_UniformLayout; }
	std::shared_ptr<Shader>& GetShader() { return m_Shader; }

	const unsigned int& GetBufferSize() const { return m_BufferSize; }

	void SetMaterialAsset(const char* filePath);

	void Serialize(const char* filePath);
	void Deserialize(const char* filePath);
};