#pragma once

#include <pch.h>

#include "IWindow.h"
#include "OpenGLContext.h"
#include "UIContext.h"

#include <render/PropertyPanel.h>
#include <render/SceneView.h>

class GLWindow : public IWindow
{
private:
	GLFWwindow* m_Window;

	bool m_IsRunning = true;
	float lastFrame = 0;
	float deltaTime = 0;

	std::unique_ptr<OpenGLContext> m_RenderCtxt;
	std::unique_ptr<UIContext> m_UICtxt;

	std::unique_ptr<SceneView> m_SceneView;
	std::unique_ptr<PropertyPanel> m_PropertyPanel;

public:

	GLWindow()
		: m_Window(nullptr), m_IsRunning(true)
	{
		m_UICtxt = std::make_unique<UIContext>();
		m_RenderCtxt = std::make_unique<OpenGLContext>();
	}

	~GLWindow();

	bool Init(int width, int height, const std::string& title);

	void Render();

	void HandleInput();

	void* GetNativeWindow() override { return m_Window; }

	void SetNativeWindow(void* window)
	{
		m_Window = (GLFWwindow*)window;
	}

	void OnScroll(double xpos, double ypos) override;

	void OnKey(int key, int scancode, int action, int mods) override;

	void OnResize(int width, int height) override;

	void OnCursor(double xpos, double ypos) override;

	void OnClose() override;

	bool IsRunning() { return m_IsRunning; }

};