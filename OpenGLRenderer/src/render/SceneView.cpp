#include <pch.h>
#include "SceneView.h"
#include <ErrorHandler.h>
#include <3rdparty/imgui/imgui.h>

void SceneView::Render(float deltaTime)
{
	m_VP->view = m_Camera->GetViewMatrix();
	m_VP->projection = m_Camera->GetProjectionMatrix();
	m_UniformBuffer->UpdateData(m_VP.get());

	for (int i = 0; i < m_Scene->m_Objects.size(); i++)
	{
		m_Scene->m_Objects[i]->Render();
	}

	if (CameraMovable)
	{
		m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
		m_Camera->Update(deltaTime);
	}
}

void SceneView::OnResize(int width, int height)
{
	m_Size.x = (float)width;
	m_Size.y = (float)height;

	m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
}
