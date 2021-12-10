#include <pch.h>
#include "SceneView.h"
#include <ErrorHandler.h>
#include <3rdparty/imgui/imgui.h>

void SceneView::Render(float deltaTime)
{
	m_Material->m_Shader->Bind();

	m_VP->view = m_Camera->GetViewMatrix();
	m_VP->projection = m_Camera->GetProjectionMatrix();
	m_UniformBuffer->UpdateData(m_VP.get());

	glm::mat4 model(1.0f);
	model = glm::translate(model, m_Position);

	m_Material->m_Shader->SetMatrix4("model", model);


	GLCall(glDrawElements(GL_TRIANGLES, m_Mesh->IndexCount, GL_UNSIGNED_INT, 0));

	//m_FrameBuffer->Unbind();

	//ImGui::Begin("Scene");

	//ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	//m_Size = { viewportPanelSize.x, viewportPanelSize.y };

	m_Camera->SetAspectRatio(m_Size.x / m_Size.y);

	//// add rendered texture to ImGUI scene window
	//uint64_t textureID = m_FrameBuffer->GetTexture();
	//ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_Size.x, m_Size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	//ImGui::End();

	if (CameraMovable)
	{
		m_Camera->Update(deltaTime);
	}
}

void SceneView::OnResize(int width, int height)
{
	m_Size.x = (float)width;
	m_Size.y = (float)height;

	m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
	//m_FrameBuffer->GenerateBuffers((int)m_Size.x, (int)m_Size.y);
}
