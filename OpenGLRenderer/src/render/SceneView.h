#pragma once

#include <pch.h>

#include <buffers/VertexBuffer.h>
#include <buffers/IndexBuffer.h>
#include <buffers/VertexArray.h>
#include <buffers/FrameBuffer.h>
#include <buffers/UniformBuffer.h>
#include <elems/Shader.h>
#include <elems/Texture2D.h>
#include <elems/Camera.h>
#include <elems/Material.h>
#include <elems/Mesh.h>
#include <ResourceManager.h>

class SceneView
{
private:
	std::shared_ptr<Texture2D> m_Texture;
	std::unique_ptr<Camera> m_Camera;
	std::unique_ptr<FrameBuffer> m_FrameBuffer;
	std::unique_ptr<UniformBuffer> m_UniformBuffer;
	std::unique_ptr<ViewProjection> m_VP;
	glm::vec2 m_Size;

public:
	std::unique_ptr<Mesh> m_Mesh;
	std::shared_ptr<Material> m_Material;
	glm::vec3 m_Position;

	

	SceneView(float deltaTime)
	{
		m_Size = glm::vec2(2560.0f, 1440.0f);
		m_FrameBuffer = std::make_unique<FrameBuffer>();
		m_FrameBuffer->GenerateBuffers(800, 600);
		//m_Shader = ResourceManager::GetShader("res/shaders/basic.vert", "res/shaders/basic.frag", nullptr);
		m_Material = std::make_shared<Material>("res/shaders/basic.vert", "res/shaders/basic.frag", nullptr);
		m_Texture = ResourceManager::GetTexture("res/textures/container.jpg");
		std::cout << ResourceManager::CheckTextureExists("res/textures/container.jpg") << std::endl;
		std::cout << ResourceManager::CheckShaderExists("res/shaders/basic.vert", "res/shaders/basic.frag", nullptr) << std::endl;
		m_UniformBuffer = std::make_unique<UniformBuffer>();
		m_VP = std::make_unique<ViewProjection>();

		m_Camera = std::make_unique<Camera>();

		m_Material->m_Shader->SetUniformBindingPoint("ViewProjection", 0);
		m_UniformBuffer->Bind();
		m_UniformBuffer->SetBindingPoint(0);

		m_VP->view = m_Camera->GetViewMatrix();
		m_VP->projection = m_Camera->GetProjectionMatrix();

		m_UniformBuffer->SetData(m_VP.get());

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};

		unsigned int indices[] = {
			2, 1, 0,
			0, 3, 2
		};

		m_Mesh = std::make_unique<Mesh>();
		m_Mesh->Load("res/models/monkey.obj");

		m_Texture->Bind(0);
		m_Material->m_Shader->Bind();
		m_Material->m_Shader->SetInteger("u_Material.tex", 0);
		
		glm::mat4 model(1.0f);
		model = glm::translate(model, m_Position);

		m_Material->m_Shader->SetMatrix4("model", model);

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