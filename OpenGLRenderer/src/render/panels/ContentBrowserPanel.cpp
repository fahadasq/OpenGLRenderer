#include "pch.h"
#include <3rdparty/imgui/imgui.h>
#include "ContentBrowserPanel.h"
#include <ResourceManager.h>
#include <utils/WindowPlatformUtils.h>

std::unordered_map<std::string, std::vector<std::filesystem::path>> ContentBrowserPanel::s_FileRepository;

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
				Asset asset = ResourceManager::AddAsset(filenameString.c_str());
				std::stringstream ss;
				ss << m_CurrentDirectory.string().c_str() << "/Asset 2.meshasset";
				std::cout << ss.str().c_str() << "\n";
				asset.Serialize(ss.str().c_str());
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

			if (ImGui::MenuItem("Create Texture Asset"))
			{
				const char* matPath = nullptr;

				std::string vfilePath = WindowFileDialog::OpenFile(".jpg");
				if (!vfilePath.empty())
				{
					matPath = vfilePath.c_str();
				}

				Asset asset = ResourceManager::AddAsset(matPath);

				std::string savePath = WindowFileDialog::SaveFile(".texasset");
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

std::string ContentBrowserPanel::GetFilesInDirectory(const std::filesystem::path& iterPath, const char* filter)
{
	for (auto& directoryEntry : std::filesystem::directory_iterator(iterPath))
	{
		const auto& path = directoryEntry.path();
		auto relativePath = std::filesystem::relative(path, s_AssetsPath);
		std::string filenameString = relativePath.filename().string();
		if (directoryEntry.is_directory())
		{
			std::filesystem::path newPath = iterPath;
			newPath /= path.filename();
			return GetFilesInDirectory(newPath, filter);
		}
		else if (filenameString.find(filter) != std::string::npos)
		{		
			s_FileRepository[filter].push_back(path);
			if (ImGui::Button(filenameString.c_str()))
			{
				return path.string();
			}
		}
	}

	return std::string();
}

std::string ContentBrowserPanel::OpenFile(const char* filter, const char* label)
{
	ImGui::Begin(label);

	std::string filePath;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::MenuItem("Refresh"))
		{
			s_FileRepository[filter].clear();
			filePath = GetFilesInDirectory(s_AssetsPath, filter);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (s_FileRepository.find(filter) != s_FileRepository.end())
	{
		for (int i = 0; i < s_FileRepository[filter].size(); i++)
		{
			if (ImGui::Button(s_FileRepository[filter][i].filename().string().c_str()))
			{
				filePath = s_FileRepository[filter][i].string();
			}
		}
	}
	else 
	{
		filePath = GetFilesInDirectory(s_AssetsPath, filter);
	}

	ImGui::End();
	return filePath;
	
}
