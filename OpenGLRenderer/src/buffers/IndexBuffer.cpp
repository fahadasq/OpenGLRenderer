#include <pch.h>
#include "IndexBuffer.h"
#include <ErrorHandler.h>

IndexBuffer::IndexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

IndexBuffer::IndexBuffer(const GLvoid* data, const GLsizeiptr& size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	m_Count = size / sizeof(unsigned int);
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::SetData(const GLvoid* data, const GLsizeiptr& size)
{
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	m_Count = size / sizeof(unsigned int);
}
