#pragma once


#include <pch.h>
#include <AssetTypes.h>

class Texture2D : public Asset
{
private:
	GLuint m_RendererID;
	unsigned int m_Width, m_Height;
public:
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image

    // texture configuration
    unsigned int Wrap_S;
    unsigned int Wrap_T;
    unsigned int Filter_Min;
    unsigned int Filter_Max;

    Texture2D();
    Texture2D(Asset asset);
    ~Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind(unsigned int slot = 0) const;
    void LoadTextureFromFile(const char* file, bool alpha = false);
};

