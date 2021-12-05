#pragma once
#include <elems/Camera.h>

struct ViewProjection {
	glm::mat4 view;
	glm::mat4 projection;
};

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

