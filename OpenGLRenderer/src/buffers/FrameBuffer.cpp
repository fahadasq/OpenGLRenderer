#include <pch.h>
#include "FrameBuffer.h"
#include <ErrorHandler.h>

FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glGenTextures(1, &m_ColorID));
	GLCall(glGenTextures(1, &m_DepthID));
}

FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
	GLCall(glDeleteTextures(1, &m_ColorID));
	GLCall(glDeleteTextures(1, &m_DepthID));
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	GLCall(glViewport(0, 0, m_Width, m_Height));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void FrameBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::DeleteBuffers()
{
	if (m_RendererID)
	{
		GLCall(glDeleteFramebuffers(1, &m_RendererID));
		if (m_ColorID)
		{
			GLCall(glDeleteTextures(1, &m_ColorID));
		}
		if (m_DepthID)
		{
			GLCall(glDeleteTextures(1, &m_DepthID));
		}
		m_ColorID = 0;
		m_DepthID = 0;
	}
}

bool FrameBuffer::GenerateBuffers(int width, int height)
{
	m_Width = width;
	m_Height = height;

	DeleteBuffers();

	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));


	GLCall(glGenTextures(1, &m_ColorID));

	GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorID));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


	GLCall(glGenTextures(1, &m_DepthID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorID, 0));	
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthID, 0));

	GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
	GLCall(glDrawBuffers(m_ColorID, buffers));

	Unbind();

	return IsStatusComplete();
}

bool FrameBuffer::IsStatusComplete()
{
	Bind();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		Unbind();
		return true;
	}
	
	Unbind();
	return false;
}
