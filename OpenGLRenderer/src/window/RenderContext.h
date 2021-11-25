#pragma once

#include "IWindow.h"

class RenderContext
{
public:
	RenderContext() : m_Window(nullptr) { }

	virtual bool Init(IWindow* window)
	{
		m_Window = window;
		return true;
	}

	virtual void PreRender() = 0;

	virtual void PostRender() = 0;

	virtual void End() = 0;

protected:
	IWindow* m_Window;
};