#include "pch.h"
#include <3rdparty/imgui/imgui.h>
#include "ContentBrowserPanel.h"
#include <ResourceManager.h>
#include <utils/WindowPlatformUtils.h>

static const std::string s_AssetsPath = std::string("res");

ContentBrowserPanel::ContentBrowserPanel()
	: m_CurrentDirectory(s_AssetsPath)
{
}

void ContentBrowserPanel::Render()
{
	ImGui::Begin("Content Browser");

	

	if (m_CurrentDirectory != std::filesystem::path(s_AssetsPath))
	{
		if (ImGui::Button("<-"))
		{
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
	}

	for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
	{
		const auto& path = directoryEntry.path();
		auto relativePath = std::filesystem::relative(path, s_AssetsPath);
		std::string filenameString = relativePath.filename().string();
		if (directoryEntry.is_directory())
		{
			if (ImGui::Button(filenameString.c_str()))
			{
				m_CurrentDirectory /= path.filename();
			}
		}
		else
		{
			if (ImGui::Button(filenameString.c_str()))
			{
				ResourceManager::AddAsset(relativePath.string().c_str());
			}
		}
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Create Shader Asset"))
			{
				const char* vertPath = nullptr;

				std::string vfilePath = WindowFileDialog::OpenFile(".vert");
				if (!vfilePath.empty())
				{
					vertPath = vfilePath.c_str();
				}

				const char* fragPath = nullptr;

				std::string ffilePath = WindowFileDialog::OpenFile(".frag");
				if (!ffilePath.empty())
				{
					fragPath = ffilePath.c_str();
				}

				ShaderAsset asset = ResourceManager::AddShaderAsset(vertPath, fragPath, nullptr);

				std::string savePath = WindowFileDialog::SaveFile(".shaderasset");
				if (!savePath.empty())
				{
					asset.Serialize(savePath.c_str());
				}

			}

			if (ImGui::MenuItem("Create Material Asset"))
			{
				const char* matPath = nullptr;

				std::string vfilePath = WindowFileDialog::OpenFile(".shaderasset");
				if (!vfilePath.empty())
				{
					matPath = vfilePath.c_str();
				}				

				Asset asset = ResourceManager::AddAsset(matPath);

				std::string savePath = WindowFileDialog::SaveFile(".matasset");
				if (!savePath.empty())
				{
					asset.Serialize(savePath.c_str());
				}

			}

			if (ImGui::MenuItem("Create Mesh Asset"))
			{
				const char* matPath = nullptr;

				std::string vfilePath = WindowFileDialog::OpenFile(".obj");
				if (!vfilePath.empty())
				{
					matPath = vfilePath.c_str();
				}

				Asset asset = ResourceManager::AddAsset(matPath);

				std::string savePath = WindowFileDialog::SaveFile(".meshasset");
				if (!savePath.empty())
				{
					asset.Serialize(savePath.c_str());
				}

			}

			ImGui::EndPopup();
		}

	}


	


	ImGui::End();
}
