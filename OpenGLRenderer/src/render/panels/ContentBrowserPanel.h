#pragma once

#include <filesystem>

class ContentBrowserPanel
{
public:
	ContentBrowserPanel();

	void Render();

private:
	std::filesystem::path m_CurrentDirectory;
};

