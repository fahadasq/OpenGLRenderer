#include "pch.h"
#include "InspectorPanel.h"
//#include <3rdparty/imguifiledialog/ImGuiFileDialog.h>
#include <utils/WindowPlatformUtils.h>
#include "ContentBrowserPanel.h"
#include <filesystem>

InspectorPanel::InspectorPanel()
{ 
    m_FilePanel = std::make_unique<AssetFilePanel>();
}

void InspectorPanel::Render(SceneView* m_Sceneview)
{
    ImGui::Begin("Properties");


    if (!m_Sceneview->m_SelectedObject.expired())
    {
        std::stringstream label;
        label << "Selected Object: " << m_Sceneview->m_SelectedObject.lock()->GetName();
        ImGui::Text(label.str().c_str());


        std::stringstream id;
        id << "Object ID: " << m_Sceneview->m_SelectedObject.lock()->GetID();
        ImGui::Text(id.str().c_str());

        DisplayObjectInfo(m_Sceneview->m_SelectedObject.lock().get());
    }
}

void InspectorPanel::DisplayUniformVariable(char* buffer, Uniform& uniform)
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

void InspectorPanel::DisplayTextureUniform(TextureUniform& uniform, std::shared_ptr<Texture2D>& texture)
{
    // open Dialog Simple
    std::string name = uniform.name;
    name = name.substr(name.find(".") + 1);

    if (ImGui::Button(name.c_str()))
    {
        m_FilePanel->Open(".texasset");
    }

    if (!m_FilePanel->GetSelected(".texasset").empty())
    {
        texture = ResourceManager::GetTexture(m_FilePanel->GetSelected(".texasset").c_str());
        m_FilePanel->Close();
        m_FilePanel->Clear();
    }
}


void InspectorPanel::DisplayObjectInfo(GameObject* object)
{
    if (ImGui::CollapsingHeader("Transform"))
    {
        ImGui::Spacing();
        Transform& transformRef = object->GetTransform();
        ImGui::DragFloat3("Position", &transformRef.m_Position.x, 0.25f);
        ImGui::DragFloat3("Rotation", &transformRef.m_Rotation.x, 0.25f);
        ImGui::DragFloat3("Scale", &transformRef.m_Scale.x, 0.25f);
    }

    ImGui::Spacing();


    if (ImGui::CollapsingHeader("Mesh"))
    {

        if (ImGui::Button("Set Mesh"))
        {
            m_FilePanel->Open(".meshasset");
        }

        if (!m_FilePanel->GetSelected(".meshasset").empty())
        {
            object->SetMesh(m_FilePanel->GetSelected(".meshasset").c_str());
            m_FilePanel->Close();
            m_FilePanel->Clear();
        }
    }

    MaterialInstance* material = object->GetMaterial();

    

    if (ImGui::CollapsingHeader("Material"))
    {
        if (material)
        {
            ImGui::Spacing();
            char* buffer = material->m_UniformBuffer;
            MaterialUniformLayout& uniformLayout = material->GetMaterialType()->GetUniformLayout();
            for (Uniform uniform : uniformLayout.uniforms)
            {
                DisplayUniformVariable(buffer, uniform);
            }
            for (size_t i = 0; i < uniformLayout.texUniforms.size(); i++)
            {
                DisplayTextureUniform(uniformLayout.texUniforms[i], material->m_Textures[i]);
            }
        }
        if (ImGui::Button("Set Material"))
        {
            m_FilePanel->Open(".matasset");
        }


        if (!m_FilePanel->GetSelected(".matasset").empty())
        {
            object->SetMaterial(m_FilePanel->GetSelected(".matasset").c_str());
            m_FilePanel->Close();
            m_FilePanel->Clear();
        }


        ImGui::Spacing();
    }

    m_FilePanel->Display();


}

