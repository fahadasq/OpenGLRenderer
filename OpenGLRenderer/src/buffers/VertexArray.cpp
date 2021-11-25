#include <pch.h>
#include "ErrorHandler.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::AddBuffer(VertexBuffer* buffer, VertexBufferLayout* layout)
{
	buffer->Bind();

	const auto& elements = layout->GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		auto element = elements[i];
		GLCall(glVertexAttribPointer(i, element.componentSize, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout->GetStride(), (void*)offset));
		GLCall(glEnableVertexAttribArray(i));
		offset += element.componentSize * VertexBufferElement::GetSizeOfType(element.type);
	}
}
