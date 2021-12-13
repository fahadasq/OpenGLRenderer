#include "pch.h"
#include "SceneHierarchyPanel.h"
#include <3rdparty/imgui/imgui_internal.h>


SceneHierarchyPanel::SceneHierarchyPanel()
{

}

void SceneHierarchyPanel::Render(SceneView* m_Sceneview)
{
    ImGui::Begin("Hierarchy");


    if (ImGui::Button("Create Object"))
    {
        m_Sceneview->m_Scene->CreateObject();
    }
    
    auto& objects = m_Sceneview->m_Scene->GetObjects();

    for (int i = 0; i < objects.size(); i++)
    {
        std::stringstream label;
        const uint64_t id = objects[i]->GetID();
        label << objects[i]->GetName();

        bool selectedObjExists = !m_Sceneview->m_SelectedObject.expired() && m_Sceneview->m_SelectedObject.lock() == objects[i];

        ImGuiTreeNodeFlags flags = ((selectedObjExists) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)objects[i].get(), flags, label.str().c_str());

        if (ImGui::IsItemClicked())
        {
            m_Sceneview->m_SelectedObject = objects[i];
        }
    }

    ImGui::End();
}
