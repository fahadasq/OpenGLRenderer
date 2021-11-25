#pragma once

#include <pch.h>

class IWindow
{
public:
	virtual void* GetNativeWindow() = 0;

	virtual void SetNativeWindow(void* window) = 0;

	virtual void OnScroll(double xpos, double ypos) = 0;

	virtual void OnKey(int key, int scancode, int action, int mods) = 0;

	virtual void OnResize(int width, int height) = 0;

	virtual void OnCursor(double xpos, double ypos) = 0;

	virtual void OnClose() = 0;

	int Width = 0;
	int Height = 0;
	std::string Title;
};