#pragma once

#include <filesystem>

class ContentBrowserPanel
{
public:
	ContentBrowserPanel();

	void Render();

	static std::string OpenFile(const char* filter, const char* label = "Select Item");

private:
	static std::string GetFilesInDirectory(const std::filesystem::path& iterPath, const char* filter);

	std::filesystem::path m_CurrentDirectory;
	static std::unordered_map<std::string, std::vector<std::filesystem::path>> s_FileRepository;
};

