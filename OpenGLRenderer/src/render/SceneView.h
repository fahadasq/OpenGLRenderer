#pragma once

#include <pch.h>

#include <buffers/VertexBuffer.h>
#include <buffers/IndexBuffer.h>
#include <buffers/VertexArray.h>
#include <buffers/FrameBuffer.h>
#include <elems/Shader.h>
#include <elems/Texture2D.h>
#include <elems/Camera.h>
#include <elems/Mesh.h>

class SceneView
{
private:
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture2D> m_Texture;
	std::unique_ptr<Camera> m_Camera;
	std::unique_ptr<FrameBuffer> m_FrameBuffer;
	glm::vec2 m_Size;

public:
	std::unique_ptr<Mesh> m_Mesh;

	SceneView(float deltaTime)
	{
		m_Size = glm::vec2(2560.0f, 1440.0f);
		m_FrameBuffer = std::make_unique<FrameBuffer>();
		m_FrameBuffer->GenerateBuffers(800, 600);
		m_Shader = std::make_unique<Shader>("res/shaders/basic.vert", "res/shaders/basic.frag", nullptr);
		m_Texture = std::make_unique<Texture2D>();
		m_Texture->LoadTextureFromFile("res/textures/container.jpg", false);

		m_Camera = std::make_unique<Camera>();

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
		m_Mesh->Load("res/models/cube.obj");

		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetInteger("container", 0);
		
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

		m_Shader->SetMatrix4("model", model);

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