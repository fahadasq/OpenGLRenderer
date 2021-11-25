#pragma once

#include "RenderContext.h"

class OpenGLContext : public RenderContext
{
public:
	bool Init(IWindow* window) override;

	void PreRender() override;
	
	void PostRender() override;

	void End() override;
};