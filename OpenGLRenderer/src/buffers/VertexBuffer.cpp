#include <pch.h>
#include "VertexBuffer.h"
#include <ErrorHandler.h>

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

VertexBuffer::VertexBuffer(const GLvoid* data, const GLsizeiptr& size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::SetData(const GLvoid* data, const GLsizeiptr& size)
{
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
