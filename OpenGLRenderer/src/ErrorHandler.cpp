#include <pch.h>
#include "ErrorHandler.h"


const char* GLCheckError(GLenum errorCode)
{
	const char* error = "";

	switch (errorCode)
	{
	case GL_INVALID_ENUM:
		error = "GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		error = "GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		error = "GL_INVALID_OPERATION";
		break;
	case GL_OUT_OF_MEMORY:
		error = "GL_OUT_OF_MEMORY";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		error = "GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	}

	return error;
}

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* file, int line)
{
	while (GLenum errorCode = glGetError())
	{
		const char* error = GLCheckError(errorCode);
		std::cout << "[OpenGL Error] " << error << std::endl;
		std::cout << file << std::endl;
		std::cout << "Line: " << line << std::endl;
		return false;
	}
	return true;
}