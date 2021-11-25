#pragma once

#include "pch.h"

#include <window/GLWindow.h>


class Application
{
public:

	Application(const std::string& app_name);

	static Application& Instance() { return *s_Instance; }

	void Loop();


private:

	static Application* s_Instance;

	std::unique_ptr<GLWindow> m_Window;
};