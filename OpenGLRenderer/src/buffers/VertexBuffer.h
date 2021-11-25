#pragma once

#include <pch.h>

class VertexBuffer
{
private:
	GLuint m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const GLvoid* data, const GLsizeiptr& size);
	~VertexBuffer();

	void Bind() const;

	void SetData(const GLvoid* data, const GLsizeiptr& size);
};