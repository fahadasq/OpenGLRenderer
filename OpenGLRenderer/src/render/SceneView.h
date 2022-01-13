#pragma once

#include <pch.h>

#include <buffers/VertexBuffer.h>
#include <buffers/IndexBuffer.h>
#include <buffers/VertexArray.h>
#include <buffers/FrameBuffer.h>
#include <buffers/UniformBuffer.h>
#include <elems/Shader.h>
#include <elems/Texture2D.h>
#include <scene/Camera.h>
#include <elems/Material.h>
#include <elems/Mesh.h>
#include <ResourceManager.h>
#include <elems/MaterialInstance.h>
#include <scene/GameObject.h>
#include <scene/Scene.h>

class SceneView
{
private:
	std::unique_ptr<Camera> m_Camera;
	std::unique_ptr<UniformBuffer> m_UniformBuffer;
	std::unique_ptr<ViewProjection> m_VP;
	std::unique_ptr<FrameBuffer> m_FrameBuffer;
	glm::vec2 m_Size;

	int m_GizmoType = 0;
	int m_GizmoMode = 0;

	bool m_MouseHovered;
	bool m_ViewportFocused = false, m_ViewportHovered = false;
	glm::vec2 m_ViewportBounds[2];

public:
	std::weak_ptr<GameObject> m_SelectedObject;
	std::unique_ptr<Scene> m_Scene;
	
	SceneView(float deltaTime)
	{
		FramebufferSpecification specs = { 2560, 1440 };
		specs.Width = 2560;
		specs.Height = 1440;
		specs.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH };
		m_FrameBuffer = std::make_unique<FrameBuffer>(specs);
		m_Size = glm::vec2(2560.0f, 1440.0f);
		m_UniformBuffer = std::make_unique<UniformBuffer>();
		m_VP = std::make_unique<ViewProjection>();
		m_Camera = std::make_unique<Camera>();
		m_Scene = std::make_unique<Scene>();

		m_UniformBuffer->Bind();
		m_VP->view = m_Camera->GetViewMatrix();
		m_VP->projection = m_Camera->GetProjectionMatrix();

		m_UniformBuffer->SetData(m_VP.get());

		m_Camera->Update(deltaTime);
		m_Camera->SetAspectRatio(m_Size.x / m_Size.y);

		
	}

	void Render(float deltaTime);

	void OnResize(int width, int height);
	void OnScroll(float deltaTime, float scroll)
	{
		m_Camera->OnScroll(deltaTime, scroll);
	}

	void HandleShortcutCommands();

	const bool& IsMouseHovered() const { return m_MouseHovered; }
	bool CameraMovable = false;
};