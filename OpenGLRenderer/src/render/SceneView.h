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
	glm::vec2 m_Size;

public:
	std::shared_ptr<GameObject> m_SelectedObject;
	std::unique_ptr<Scene> m_Scene;
	

	SceneView(float deltaTime)
	{
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

	bool CameraMovable = false;
};