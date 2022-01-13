#pragma once

#include <UUID.h>
#include <buffers/VertexBuffer.h>
#include <buffers/IndexBuffer.h>
#include <buffers/VertexArray.h>
#include <AssetTypes.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh : public Asset
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
	Mesh(Asset asset);
	~Mesh();

	void CreateBuffers();
	void DeleteBuffers();
	void Bind();

	unsigned int IndexCount;

	void SetAsset(const char* filePath);

	void Load(const std::string filepath);

	const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
	const std::vector<unsigned int>& GetIndices() const { return m_Indices; }

	void Serialize(const std::string& filepath);
	void Deserialize(const std::string& filepath);
};

