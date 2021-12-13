#include <pch.h>
#include "GLWindow.h"
#include <Input.h>


bool GLWindow::Init(int width, int height, const std::string& title)
{
	Width = width;
	Height = height;
	Title = title;

	m_RenderCtxt->Init(this);
	m_UICtxt->Init(this);

	m_SceneView = std::make_unique<SceneView>(deltaTime);
	m_PropertyPanel = std::make_unique<PropertyPanel>();

	return true;
}

GLWindow::~GLWindow()
{
	m_UICtxt->End();
	m_RenderCtxt->End();
}

void GLWindow::Render()
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	m_RenderCtxt->PreRender();
	m_UICtxt->PreRender();


	m_SceneView->Render(deltaTime);
	m_PropertyPanel->Render(m_SceneView.get());

	m_UICtxt->PostRender();
	m_RenderCtxt->PostRender();

	HandleInput();
}

void GLWindow::HandleInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_IsRunning = false;
	}

	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);

	Input::MouseCallback(xpos, ypos);


	if (Input::GetPressedButton((GLFWwindow*)GetNativeWindow()) == EInputButton::Right && !m_SceneView->CameraMovable)
	{
		m_SceneView->CameraMovable = true;
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if (Input::GetPressedButton((GLFWwindow*)GetNativeWindow()) != EInputButton::Right && m_SceneView->CameraMovable)
	{
		m_SceneView->CameraMovable = false;
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void GLWindow::OnScroll(double xpos, double ypos)
{
	m_SceneView->OnScroll(deltaTime, (float)ypos);
	Input::ScrollCallback(xpos, ypos);
}

void GLWindow::OnKey(int key, int scancode, int action, int mods)
{
	Input::KeyCallback(key, scancode, action, mods);	
}

void GLWindow::OnResize(int width, int height)
{
	Width = width;
	Height = height;

	m_SceneView->OnResize(Width, Height);
	Render();
}

void GLWindow::OnCursor(double xpos, double ypos)
{
	Input::MouseCallback(xpos, ypos);
}

void GLWindow::OnClose()
{
	m_IsRunning = false;
}
