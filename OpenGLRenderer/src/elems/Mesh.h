#pragma once

#include <buffers/VertexBuffer.h>
#include <buffers/IndexBuffer.h>
#include <buffers/VertexArray.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
private:
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<VertexBufferLayout> m_BufferLayout;
	std::unique_ptr<VertexArray> m_VertexArray;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

public:
	Mesh();
	~Mesh();

	void CreateBuffers();
	void DeleteBuffers();
	void Bind() const;

	unsigned int IndexCount;

	void Load(const std::string& filepath);
};

