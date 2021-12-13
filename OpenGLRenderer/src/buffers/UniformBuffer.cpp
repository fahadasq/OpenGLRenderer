#include "pch.h"
#include <ErrorHandler.h>
#include "UniformBuffer.h"

UniformBuffer::UniformBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

UniformBuffer::UniformBuffer(const GLsizeiptr& size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW));
}

UniformBuffer::~UniformBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void UniformBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
}

void UniformBuffer::SetData(ViewProjection* vp)
{	
	Bind();
	SetBindingPoint(ViewProjection::slot);
	GLCall(glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewProjection), vp, GL_DYNAMIC_DRAW));
}

void UniformBuffer::UpdateData(ViewProjection* vp)
{
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(vp->view)));
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(vp->projection)));
}

void UniformBuffer::SetBindingPoint(const unsigned int index)
{
	GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, index, m_RendererID));
}
