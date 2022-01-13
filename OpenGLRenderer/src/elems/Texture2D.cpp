#include <pch.h>
#include "Texture2D.h"
#include <ErrorHandler.h>
#include <3rdparty/stb_image/stb_image.h>

Texture2D::Texture2D()
	: m_Width(0), m_Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
	Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	m_UUID = UniversallyUniqueID();
	m_SourceFilePath = std::string();
	m_Type = AssetType::Texture2D;
	GLCall(glGenTextures(1, &m_RendererID));
}

Texture2D::Texture2D(Asset asset)
{
	m_UUID = asset.GetID();
	m_SourceFilePath = asset.GetSourcePath();
	m_Type = AssetType::Texture2D;
	GLCall(glGenTextures(1, &m_RendererID));
	LoadTextureFromFile(m_SourceFilePath.c_str());
}

Texture2D::~Texture2D()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	m_Width = width;
	m_Height = height;
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, NULL, Image_Format, GL_UNSIGNED_BYTE, data));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max));
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture2D::LoadTextureFromFile(const char* file, bool alpha)
{
	if (alpha)
	{
		Internal_Format = GL_RGBA;
		Image_Format = GL_RGBA;
	}
	// load image
	std::cout << "File Path TextureGen: " << file << std::endl;
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	// now generate texture
	Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	m_SourceFilePath = std::string(file);
}
