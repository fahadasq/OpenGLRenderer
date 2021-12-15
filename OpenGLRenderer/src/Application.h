#pragma once

#include "pch.h"

#include <window/GLWindow.h>


static class Application
{
public:


	static Application& Instance() { return *s_Instance; }

	static void Init(const std::string& app_name);
	static void Loop();

	static GLFWwindow* GetNativeWindow();

private:
	static std::unique_ptr<GLWindow> m_Window;
	Application() { }

	static Application* s_Instance;

};