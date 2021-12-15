#include <pch.h>
#include <Application.h>

std::unique_ptr<GLWindow> Application::m_Window;

void Application::Init(const std::string& app_name)
{
	m_Window = std::make_unique<GLWindow>();
	m_Window->Init(1920, 1080, app_name);
}

void Application::Loop()
{
	while (m_Window->IsRunning())
	{
		m_Window->Render();
	}
}

GLFWwindow* Application::GetNativeWindow()
{
	return (GLFWwindow*)m_Window->GetNativeWindow();
}
