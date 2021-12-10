#include <pch.h>
#include "PropertyPanel.h"
#include <3rdparty/imguifiledialog/ImGuiFileDialog.h>
#include <ResourceManager.h>

void PropertyPanel::Render(SceneView* m_Sceneview)
{
    ImGui::Begin("Window");
    ImGui::Text("Hello World!");

    ImGuiIO& io = ImGui::GetIO();

    // open Dialog Simple
    if (ImGui::Button("Set Mesh"))
        ImGuiFileDialog::Instance()->OpenDialog("SetMesh", "Choose File", ".obj", ".");

    // display
    if (ImGuiFileDialog::Instance()->Display("SetMesh"))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            m_SetMeshCallback(filePathName);
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }

    char* buffer = m_Sceneview->m_Material->m_UniformBuffer;
    for (Uniform i : m_Sceneview->m_Material->m_UniformLayout->uniforms)
    {
        DisplayUniformVariable(buffer, i);
    }
    for (int i = 0; i < m_Sceneview->m_Material->m_UniformLayout->texUniforms.size(); i++)
    {
        DisplayTextureUniform(m_Sceneview->m_Material->m_UniformLayout->texUniforms[i]);
    }

    ImGui::SliderFloat3("Position", &m_Sceneview->m_Position.x, -5.0f, 5.0f);

    m_Sceneview->m_Material->SetUniforms();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void PropertyPanel::DisplayUniformVariable(char* buffer, Uniform& uniform)
{
    switch (uniform.type)
    {
    case GL_FLOAT:
        ImGui::InputFloat(uniform.name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_FLOAT_VEC2:
        ImGui::InputFloat2(uniform.name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_FLOAT_VEC3:
        ImGui::ColorEdit3(uniform.name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_FLOAT_VEC4:
        ImGui::InputFloat4(uniform.name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_INT:
        ImGui::InputInt(uniform.name.c_str(), (int*)&buffer[uniform.offset]);
        break;
    }
}

void PropertyPanel::DisplayTextureUniform(TextureUniform& uniform)
{
    // open Dialog Simple
    if (ImGui::Button(uniform.name.c_str()))
        ImGuiFileDialog::Instance()->OpenDialog("SetTexture", "Choose File", ".png,.jpg,.jpeg", ".");

    // display
    if (ImGuiFileDialog::Instance()->Display("SetTexture"))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            uniform.texture = ResourceManager::GetTexture(filePathName.c_str());
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}
