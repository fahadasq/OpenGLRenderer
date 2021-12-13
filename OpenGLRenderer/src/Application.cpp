#include <pch.h>
#include <Application.h>


Application::Application(const std::string& app_name)
{	
	m_Window = std::make_unique<GLWindow>();
	m_Window->Init(2560, 1440, app_name);
}

void Application::Loop()
{
	while (m_Window->IsRunning())
	{
		m_Window->Render();
	}
}