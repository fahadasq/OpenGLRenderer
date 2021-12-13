#include <pch.h>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Mesh::Mesh()
{
    m_VertexBuffer = std::make_unique<VertexBuffer>();
    m_IndexBuffer = std::make_unique<IndexBuffer>();
    m_BufferLayout = std::make_unique<VertexBufferLayout>();
    m_VertexArray = std::make_unique<VertexArray>();
}

Mesh::~Mesh()
{
}

void Mesh::CreateBuffers()
{
    m_VertexBuffer->Bind();
    m_IndexBuffer->Bind();

    m_VertexBuffer->SetData(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));
    m_IndexBuffer->SetData(&m_Indices[0], m_Indices.size() * sizeof(unsigned int));

    m_BufferLayout->Push<float>(3);
    m_BufferLayout->Push<float>(3);
    m_BufferLayout->Push<float>(2);

    m_VertexArray->Bind();
    m_VertexArray->AddBuffer(m_VertexBuffer.get(), m_BufferLayout.get());

    IndexCount = m_IndexBuffer->GetCount();
}

void Mesh::DeleteBuffers()
{    
    m_BufferLayout->Clear();

    if (!m_Vertices.empty())
    {
        m_Vertices.clear();
    }
    if (!m_Indices.empty())
    {
        m_Indices.clear();
    }
}

void Mesh::Bind()
{
    m_VertexArray->Bind();
    m_IndexBuffer->Bind();
    m_VertexBuffer->Bind();
    IndexCount = m_IndexBuffer->GetCount();
}

void Mesh::Load(const std::string& filepath)
{
    const unsigned int cMeshImportFlags =
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_SortByPType |
        aiProcess_GenNormals |
        aiProcess_GenUVCoords |
        aiProcess_OptimizeMeshes |
        aiProcess_ValidateDataStructure;

    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(filepath.c_str(),
        cMeshImportFlags);

    if (pScene && pScene->HasMeshes())
    {
        auto* mesh = pScene->mMeshes[0];

        DeleteBuffers();

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
            if (mesh->mTextureCoords[0])
            {
                vertex.TexCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            }
            m_Vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                m_Indices.push_back(face.mIndices[j]);
            }
        }

        CreateBuffers();
    }
}
