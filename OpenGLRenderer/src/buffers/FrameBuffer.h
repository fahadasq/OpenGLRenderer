#pragma once

#include <pch.h>

class FrameBuffer
{
private:
	GLuint m_RendererID;
	GLuint m_ColorID = 0;
	GLuint m_DepthID = 0;
	int m_Width;
	int m_Height;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;

	void DeleteBuffers();
	bool GenerateBuffers(int width, int height);

	bool IsStatusComplete();

	GLuint GetTexture() { return m_ColorID; }
};