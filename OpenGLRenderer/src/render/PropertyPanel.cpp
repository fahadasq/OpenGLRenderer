#include <pch.h>
#include "PropertyPanel.h"
#include <3rdparty/imguifiledialog/ImGuiFileDialog.h>

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

    ImGui::SliderFloat3("Position", &m_Sceneview->m_Position.x, -5.0f, 5.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}
