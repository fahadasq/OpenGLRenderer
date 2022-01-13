#pragma once

#include <pch.h>

enum class FramebufferTextureFormat
{
	None = 0,

	// Color
	RGBA8,
	RED_INTEGER,

	// Depth/Stencil
	DEPTH24STENCIL8,

	// Defaults
	DEPTH = DEPTH24STENCIL8

};

struct FramebufferTextureSpecification
{
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format)
		: TextureFormat(format) { }

	FramebufferTextureFormat TextureFormat;
	// TODO: filtering/wrap
};

struct FramebufferAttachmentSpecification
{
	FramebufferAttachmentSpecification() = default;
	FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
		: Attachments(attachments) { }

	std::vector<FramebufferTextureSpecification> Attachments;
};

struct FramebufferSpecification
{
	unsigned int Width;
	unsigned int Height;
	FramebufferAttachmentSpecification Attachments;
};

class FrameBuffer
{
private:
	GLuint m_RendererID;
	std::vector<GLuint> m_ColorAttachments;
	GLuint m_DepthAttachment = 0;
	FramebufferSpecification m_Specification;

	std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
	FramebufferTextureSpecification m_DepthAttachmentSpecification;

public:
	FrameBuffer(const FramebufferSpecification& specs);
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;

	void Invalidate();

	

	void DeleteBuffers();
	/*bool GenerateBuffers(int width, int height, GLenum internalFormat = GL_RGB, GLenum format = GL_RGB);
	bool AddColorAttachment(uint32_t attachmentIndex, GLenum internalFormat, GLenum format);*/

	bool IsStatusComplete();

	int ReadPixel(uint32_t attachmentIndex, int x, int y);

	void Resize(int width, int height);

	GLuint GetTextureAttachment(uint32_t attachmentIndex) { return m_ColorAttachments[attachmentIndex]; }
	GLuint GetDepthAttachment() { return m_DepthAttachment; }
};