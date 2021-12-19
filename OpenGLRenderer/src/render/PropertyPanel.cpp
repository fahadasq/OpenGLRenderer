#include <pch.h>
#include "PropertyPanel.h"
#include <ResourceManager.h>

void EditorView::Render(SceneView* m_Sceneview)
{
    ImGuiIO& io = ImGui::GetIO();

    

    m_HierarchyPanel->Render(m_Sceneview);
    m_InspectorPanel->Render(m_Sceneview);
    m_ContentPanel->Render();
    m_StatsPanel->Render();
    

    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}



