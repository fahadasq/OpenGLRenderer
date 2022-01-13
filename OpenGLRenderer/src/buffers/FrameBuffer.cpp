#include <pch.h>
#include "FrameBuffer.h"
#include <ErrorHandler.h>

namespace Utils
{

	static bool IsDepthFormat(FramebufferTextureFormat format)
	{
		switch (format)
		{
		case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
		}

		return false;
	}

	static void CreateTextures(GLuint count, GLuint* outID)
	{
		GLCall(glGenTextures(count, outID));
	}

	static void BindTexture(GLuint ID)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, ID));
	}

	static void AttachColorTexture(GLuint ID, GLenum internalFormat, GLenum format, unsigned int width, unsigned int height, int index)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, ID, 0));
	}

	static void AttachDepthTexture(GLuint ID, GLenum format, unsigned int width, unsigned int height)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ID, 0));
	}
}

FrameBuffer::FrameBuffer(const FramebufferSpecification& specs)
{
	m_Specification = specs;

	for (auto format : m_Specification.Attachments.Attachments)
	{
		if (!Utils::IsDepthFormat(format.TextureFormat))
			m_ColorAttachmentSpecifications.emplace_back(format);
		else
			m_DepthAttachmentSpecification = format;
	}

	Invalidate();
}

void FrameBuffer::Resize(int width, int height)
{
	m_Specification.Width = width;
	m_Specification.Height = height;

	Invalidate();

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

FrameBuffer::~FrameBuffer()
{
	DeleteBuffers();
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	GLCall(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void FrameBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Invalidate()
{
	DeleteBuffers();

	GLCall(glGenFramebuffers(1, &m_RendererID));

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

	// Attachments

	if (m_ColorAttachmentSpecifications.size())
	{
		m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
		Utils::CreateTextures(m_ColorAttachments.size(), m_ColorAttachments.data());

		for (size_t i = 0; i < m_ColorAttachments.size(); i++)
		{
			Utils::BindTexture(m_ColorAttachments[i]);

			switch (m_ColorAttachmentSpecifications[i].TextureFormat)
			{
			case FramebufferTextureFormat::RGBA8:				
				Utils::AttachColorTexture(m_ColorAttachments[i], GL_RGBA8, GL_RGBA,m_Specification.Width, m_Specification.Height, i);
				break;
			case FramebufferTextureFormat::RED_INTEGER:
				Utils::AttachColorTexture(m_ColorAttachments[i], GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
				break;
			}
		}
	}

	if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
	{
		Utils::CreateTextures(1, &m_DepthAttachment);
		Utils::BindTexture(m_DepthAttachment);

		switch (m_DepthAttachmentSpecification.TextureFormat)
		{
		case FramebufferTextureFormat::DEPTH24STENCIL8:
			Utils::AttachDepthTexture(m_DepthAttachment, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		}
	}

	if (m_ColorAttachments.size() > 1)
	{
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		GLCall(glDrawBuffers(m_ColorAttachments.size(), buffers));
	}
	else if (m_ColorAttachments.empty())
	{
		GLCall(glDrawBuffer(GL_NONE));
	}

	Unbind();
}

void FrameBuffer::DeleteBuffers()
{
	if (m_RendererID)
	{
		GLCall(glDeleteFramebuffers(1, &m_RendererID));
		if (m_ColorAttachments.size())
		{
			GLCall(glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data()));
		}
		if (m_DepthAttachment)
		{
			GLCall(glDeleteTextures(1, &m_DepthAttachment));
		}
		m_ColorAttachments.clear();
		m_DepthAttachment = 0;
	}
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

int FrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
{
	//GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex));
	int pixelData;
	GLCall(glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData));
	return pixelData;
	//Unbind();
}
