#include <pch.h>
#include "PropertyPanel.h"

void PropertyPanel::Render(SceneView* m_Sceneview)
{
    ImGui::Begin("Window");
    ImGui::Text("Hello World!");

    ImGuiIO& io = ImGui::GetIO();    

    if (ImGui::Button("Set Mesh"))
    {
        m_SetMeshCallback("res/models/quad.obj");
    }

    ImGui::SliderFloat3("Position", &m_Sceneview->m_Position.x, -5.0f, 5.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}
