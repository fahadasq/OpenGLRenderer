#include "pch.h"
#include "InspectorPanel.h"
#include <3rdparty/imguifiledialog/ImGuiFileDialog.h>
#include <utils/WindowPlatformUtils.h>

InspectorPanel::InspectorPanel()
{ 

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

        DisplayObjectInfo(m_Sceneview->m_SelectedObject.lock().get(), m_Sceneview);
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

void InspectorPanel::DisplayTextureUniform(TextureUniform& uniform)
{
    // open Dialog Simple
    std::string name = uniform.name;
    name = name.substr(name.find(".") + 1);

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

void InspectorPanel::DisplayObjectInfo(GameObject* object, SceneView* m_Sceneview)
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
        ImGui::Spacing();
        // open Dialog Simple
        if (ImGui::Button("Open..."))
        {
            std::string filePath = WindowFileDialog::OpenFile(".obj");
            if (!filePath.empty())
            {
                object->SetMesh(filePath.c_str());
            }
            //ImGuiFileDialog::Instance()->OpenDialog("SetMesh", "Choose File", ".obj", ".");
        }

        //// display
        //if (ImGuiFileDialog::Instance()->Display("SetMesh"))
        //{
        //    // action if OK
        //    if (ImGuiFileDialog::Instance()->IsOk())
        //    {
        //        std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
        //        std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
        //        object->SetMesh(filePathName.c_str());
        //    }

        //    // close
        //    ImGuiFileDialog::Instance()->Close();
        //}

        //ImGui::Spacing();
    }

    ImGui::Spacing();

    MaterialInstance* material = object->GetMaterial();

    if (ImGui::CollapsingHeader("Material") && material)
    {
        ImGui::Spacing();
        char* buffer = material->m_UniformBuffer;
        std::shared_ptr<MaterialUniformLayout> uniformLayout = material->GetMaterialType()->GetUniformLayout();
        for (Uniform uniform : uniformLayout->uniforms)
        {
            DisplayUniformVariable(buffer, uniform);
        }
        for (size_t i = 0; i < uniformLayout->texUniforms.size(); i++)
        {
            DisplayTextureUniform(uniformLayout->texUniforms[i]);
        }

        ImGui::Spacing();

        material->SetUniforms();
    }


}

