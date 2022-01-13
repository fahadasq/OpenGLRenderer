#include "pch.h"
#include "AssetFilePanel.h"
#include "ContentBrowserPanel.h"
#include <3rdparty/imgui/imgui.h>

static const std::string s_AssetsPath = std::string("res");

std::unordered_map<std::string, std::vector<std::filesystem::path>> AssetFilePanel::s_FileRepository;


void AssetFilePanel::Open(const char* filter)
{
	m_IsOpen = true;
	m_Filter = filter;
	m_Selected.clear();
}

void AssetFilePanel::Display(const char* label)
{
	if (!m_IsOpen) return;

	ImGui::Begin(label);


	if (ImGui::BeginMenuBar())
	{
		if (ImGui::MenuItem("Refresh"))
		{
			s_FileRepository[m_Filter].clear();
			GetFilesInDirectory(s_AssetsPath, m_Filter);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (s_FileRepository.find(m_Filter) != s_FileRepository.end())
	{
		for (int i = 0; i < s_FileRepository[m_Filter].size(); i++)
		{
			if (ImGui::Button(s_FileRepository[m_Filter][i].filename().string().c_str()))
			{
				m_Selected = s_FileRepository[m_Filter][i].string();
				Close();
			}
		}
	}
	else
	{
		GetFilesInDirectory(s_AssetsPath, m_Filter);
	}

	ImGui::End();
}

void AssetFilePanel::Close()
{
	m_IsOpen = false;
}

void AssetFilePanel::Clear()
{
	m_Selected.clear();
}

std::string AssetFilePanel::GetSelected(const char* filter)
{
	if (m_Filter == filter) 
		return m_Selected;

	return std::string();
}

void AssetFilePanel::GetFilesInDirectory(const std::filesystem::path& iterPath, const char* filter)
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
			GetFilesInDirectory(newPath, filter);
		}
		else if (filenameString.find(filter) != std::string::npos)
		{
			s_FileRepository[filter].push_back(path);
		}
	}
}
