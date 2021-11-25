#pragma once

#include <pch.h>

class IndexBuffer
{
private:
	GLuint m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const GLvoid* data, const GLsizeiptr& size);
	~IndexBuffer();

	void Bind() const;

	void SetData(const GLvoid* data, const GLsizeiptr& size);
	
	const unsigned int& GetCount() const { return m_Count; }
};