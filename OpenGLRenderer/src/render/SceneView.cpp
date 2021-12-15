#include <pch.h>
#include "SceneView.h"
#include <ErrorHandler.h>
#include <3rdparty/imgui/imgui.h>

void SceneView::Render(float deltaTime)
{
	m_VP->view = m_Camera->GetViewMatrix();
	m_VP->projection = m_Camera->GetProjectionMatrix();
	m_UniformBuffer->UpdateData(m_VP.get());

	m_FrameBuffer->Bind();

	m_Scene->Render();

	m_FrameBuffer->Unbind();

	ImGui::Begin("Scene");

	
	m_MouseHovered = ImGui::IsWindowHovered();

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_Size = { viewportPanelSize.x, viewportPanelSize.y };

	m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
	if (CameraMovable)
	m_Camera->Update(deltaTime);

	// add rendered texture to ImGUI scene window
	uint64_t textureID = m_FrameBuffer->GetTexture();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_Size.x, m_Size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();


	/*if (CameraMovable)
	{
		m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
		m_Camera->Update(deltaTime);
	}*/
}

void SceneView::OnResize(int width, int height)
{
	m_Size.x = (float)width;
	m_Size.y = (float)height;

	m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
}
