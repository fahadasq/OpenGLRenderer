#pragma once
#include <scene/Camera.h>
#include <elems/UniformBufferStructs.h>



class UniformBuffer
{
private:
	GLuint m_RendererID;
public:
	UniformBuffer();
	UniformBuffer(const GLsizeiptr& size);
	~UniformBuffer();

	void Bind() const;

	void SetData(ViewProjection* vp);
	void UpdateData(ViewProjection* vp);
	void SetBindingPoint(const unsigned int index);
};

