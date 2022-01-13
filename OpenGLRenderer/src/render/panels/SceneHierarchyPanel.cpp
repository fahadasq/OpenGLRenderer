#include "pch.h"
#include "SceneHierarchyPanel.h"
#include <3rdparty/imgui/imgui_internal.h>


SceneHierarchyPanel::SceneHierarchyPanel()
{

}

void SceneHierarchyPanel::Render(SceneView* m_Sceneview)
{
    ImGui::Begin("Hierarchy");

	
    uint64_t selectedID = 0;

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("Default Object"))
        {
            m_Sceneview->m_Scene->CreateObject();
        }

        ImGui::EndPopup();
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

        if (ImGui::IsItemClicked(0))
        {
            m_Sceneview->m_SelectedObject = objects[i];
            selectedID = id;
        }

        ImGui::OpenPopupOnItemClick("SelectedItem", ImGuiPopupFlags_MouseButtonRight);
    
        

    }

    if (ImGui::BeginPopupContextItem("SelectedItem"))
    {
        if (ImGui::MenuItem("Delete Object"))
        {
            m_Sceneview->m_Scene->RemoveObject(selectedID);
        }

        ImGui::EndPopup();
    }
    

    ImGui::End();
}
