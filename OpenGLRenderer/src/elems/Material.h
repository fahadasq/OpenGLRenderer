#pragma once

#include "Shader.h"
#include "Texture2D.h"

class Material
{
private:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<MaterialUniformLayout> m_UniformLayout;
	unsigned int m_BufferSize;

public:

	Material();
	Material(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
	~Material();


	void Bind() const;
	void SetUniformBindingPoint(const char* name, const unsigned int index);
	void Generate(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	std::shared_ptr<MaterialUniformLayout>& GetUniformLayout() { return m_UniformLayout; }
	std::shared_ptr<Shader>& GetShader() { return m_Shader; }

	const unsigned int& GetBufferSize() const { return m_BufferSize; }
};