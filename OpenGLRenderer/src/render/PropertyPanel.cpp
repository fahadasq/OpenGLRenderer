#include <pch.h>
#include "PropertyPanel.h"
#include <3rdparty/imguifiledialog/ImGuiFileDialog.h>
#include <ResourceManager.h>

void PropertyPanel::Render(SceneView* m_Sceneview)
{
    ImGui::Begin("Hierarchy");

    ImGuiIO& io = ImGui::GetIO();
    
    if (ImGui::Button("Create Object"))
    {
        m_Sceneview->m_Scene->CreateObject();
    }

    for (int i = 0; i < m_Sceneview->m_Scene->m_Objects.size(); i++)
    {
        std::stringstream label;
        const uint64_t id = m_Sceneview->m_Scene->m_Objects[i]->GetID();
        label << m_Sceneview->m_Scene->m_Objects[i]->m_Name << id;

        ImGuiTreeNodeFlags flags = ((m_Sceneview->m_SelectedObject == m_Sceneview->m_Scene->m_Objects[i]) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)m_Sceneview->m_Scene->m_Objects[i].get(), flags, label.str().c_str());

        if (ImGui::IsItemClicked())
        {
            m_Sceneview->m_SelectedObject = m_Sceneview->m_Scene->m_Objects[i];
        }
    }

    ImGui::End();

    ImGui::Begin("Properties");

    if (m_Sceneview->m_SelectedObject)
    {
        std::stringstream label;
        label << "Selected Object: "<< m_Sceneview->m_SelectedObject->m_Name << m_Sceneview->m_SelectedObject->GetID();
        ImGui::Text(label.str().c_str());
        DisplayObjectInfo(m_Sceneview->m_SelectedObject.get());
    }
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void PropertyPanel::DisplayUniformVariable(char* buffer, Uniform& uniform)
{
    std::string name = uniform.name;
    name = name.substr(name.find(".") + 1);

    switch (uniform.type)
    {
    case GL_FLOAT:
        ImGui::InputFloat(name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_FLOAT_VEC2:
        ImGui::InputFloat2(name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_FLOAT_VEC3:
        ImGui::ColorEdit3(name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_FLOAT_VEC4:
        ImGui::InputFloat4(name.c_str(), (float*)&buffer[uniform.offset]);
        break;
    case GL_INT:
        ImGui::InputInt(name.c_str(), (int*)&buffer[uniform.offset]);
        break;
    }
}

void PropertyPanel::DisplayTextureUniform(TextureUniform& uniform)
{
    // open Dialog Simple
    std::string name = uniform.name;
    name = name.substr(name.find(".") +1);

    if (ImGui::Button(name.c_str()))
        ImGuiFileDialog::Instance()->OpenDialog("SetTexture", "Choose File", ".jpg,.jpeg,.png", ".");

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

void PropertyPanel::DisplayObjectInfo(GameObject* object)
{   
        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::DragFloat3("Position", &object->m_Transform.m_Position.x);
            ImGui::DragFloat3("Rotation", &object->m_Transform.m_Rotation.x);
            ImGui::DragFloat3("Scale", &object->m_Transform.m_Scale.x);
        }

        if (ImGui::CollapsingHeader("Mesh"))
        {
            // open Dialog Simple
            if (ImGui::Button("Open..."))
                ImGuiFileDialog::Instance()->OpenDialog("SetMesh", "Choose File", ".obj", ".");


            // display
            if (ImGuiFileDialog::Instance()->Display("SetMesh"))
            {
                // action if OK
                if (ImGuiFileDialog::Instance()->IsOk())
                {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                    object->SetMesh(filePathName.c_str());
                }

                // close
                ImGuiFileDialog::Instance()->Close();
            }

            ImGui::Spacing();
        }


        if (ImGui::CollapsingHeader("Material"))
        {
            char* buffer = object->m_Material->m_UniformBuffer;
            for (Uniform uniform : object->m_Material->m_MaterialType->m_UniformLayout->uniforms)
            {
                DisplayUniformVariable(buffer, uniform);
            }
            for (size_t i = 0; i < object->m_Material->m_MaterialType->m_UniformLayout->texUniforms.size(); i++)
            {
                DisplayTextureUniform(object->m_Material->m_MaterialType->m_UniformLayout->texUniforms[i]);
            }

            
            object->m_Material->SetUniforms();
        }

    
}


