#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"

class VertexArray
{
private:
	GLuint m_RendererID;

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer* buffer, VertexBufferLayout* layout);
	void Bind();
};