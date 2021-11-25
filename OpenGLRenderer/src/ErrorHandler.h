#pragma once

#include <pch.h>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();	x;	ASSERT(GLLogError(__FILE__, __LINE__));

const char* GLCheckError(GLenum errorCode);

void GLClearError();

bool GLLogError(const char* file, int line);
