#include <pch.h>
#include "SceneView.h"
#include <ErrorHandler.h>
#include <3rdparty/imgui/imgui.h>
#include <3rdparty/imguizmo/ImGuizmo.h>
#include <Input.h>
#include <Application.h>
#include <utils/MathUtils.h>

void SceneView::Render(float deltaTime)
{
	HandleShortcutCommands();

	m_VP->view = m_Camera->GetViewMatrix();
	m_VP->projection = m_Camera->GetProjectionMatrix();
	m_UniformBuffer->UpdateData(m_VP.get());

	m_FrameBuffer->Bind();

	m_Scene->Render();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Scene");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_Size != *((glm::vec2*)&viewportPanelSize))
	{
		m_Size = { viewportPanelSize.x, viewportPanelSize.y };
		m_FrameBuffer->Resize((int)m_Size.x, (int)m_Size.y);
		m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
	}
	auto viewportOffset = ImGui::GetCursorPos();

	m_MouseHovered = ImGui::IsWindowHovered();


	if (CameraMovable)
		m_Camera->Update(deltaTime);

	// Add rendered texture to ImGUI scene window
	uint64_t textureID = m_FrameBuffer->GetTextureAttachment(0);
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_Size.x, m_Size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


	// Gizmos
	if (!m_SelectedObject.expired() && m_GizmoType != -1 && m_GizmoMode != -1)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		glm::mat4 cameraView = m_Camera->GetViewMatrix();
		const glm::mat4& cameraProjection = m_Camera->GetProjectionMatrix();

		auto& transform = m_SelectedObject.lock()->GetTransform();
		glm::mat4 model = transform.GetModel();

		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
			(ImGuizmo::OPERATION)m_GizmoType, (ImGuizmo::MODE)m_GizmoMode, glm::value_ptr(model));

		if (ImGuizmo::IsUsing())
		{
			glm::vec3 translation, rotation, scale;
			Math::DecomposeTransform(model, translation, rotation, scale);

			glm::vec3 euler = glm::degrees(rotation);

			glm::vec3 deltaRotation = euler - transform.m_Rotation;

			transform.m_Position = translation;
			transform.m_Rotation += deltaRotation;
			transform.m_Scale = scale;
		}

		
	}

	auto windowSize = ImGui::GetWindowSize();
	ImVec2 minBound = ImGui::GetWindowPos();
	minBound.x += viewportOffset.x;
	minBound.y += viewportOffset.y;

	ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
	m_ViewportBounds[0] = { minBound.x, minBound.y };
	m_ViewportBounds[1] = { maxBound.x, maxBound.y };

	auto [mx, my] = ImGui::GetMousePos();
	mx -= m_ViewportBounds[0].x;
	my -= m_ViewportBounds[0].y;
	glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
	my = viewportSize.y - my;

	int mouseX = (int)mx;
	int mouseY = (int)my;

	if (Input::GetPressedButton((GLFWwindow*)Application::GetNativeWindow()) == EInputButton::Left && m_MouseHovered && !ImGuizmo::IsUsing())
	{
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixel = m_FrameBuffer->ReadPixel(1, mouseX, mouseY);
			m_SelectedObject = m_Scene->GetObjectAtIndex(pixel);
		}
	}

	m_FrameBuffer->Unbind();

	ImGui::End();
	ImGui::PopStyleVar();
}

void SceneView::OnResize(int width, int height)
{
	m_Size.x = (float)width;
	m_Size.y = (float)height;

	m_Camera->SetAspectRatio(m_Size.x / m_Size.y);
	m_FrameBuffer->Resize(m_Size.x, m_Size.y);
}

void SceneView::HandleShortcutCommands()
{
	if (CameraMovable) { return; }

	if (Input::Keys[GLFW_KEY_Q])
	{
		m_GizmoType = -1;
	}
	if (Input::Keys[GLFW_KEY_W])
	{
		m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
	}
	if (Input::Keys[GLFW_KEY_E])
	{
		m_GizmoType = ImGuizmo::OPERATION::ROTATE;
	}
	if (Input::Keys[GLFW_KEY_R])
	{
		m_GizmoType = ImGuizmo::OPERATION::SCALE;
	}
	if (Input::Keys[GLFW_KEY_Z])
	{
		m_GizmoMode = ImGuizmo::MODE::LOCAL;
	}
	if (Input::Keys[GLFW_KEY_X])
	{
		m_GizmoMode = ImGuizmo::MODE::WORLD;
	}
}
