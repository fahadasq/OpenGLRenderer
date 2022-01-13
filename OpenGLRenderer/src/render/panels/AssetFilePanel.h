#pragma once
class AssetFilePanel
{
public:

	void Open(const char* filter);

	void Display(const char* label = "Select Item");

	void Close();

	void Clear();

	std::string GetSelected(const char* filter);

private:

	bool m_IsOpen;
	const char* m_Filter;

	std::string m_Selected;

	static void GetFilesInDirectory(const std::filesystem::path& iterPath, const char* filter);
	static std::unordered_map<std::string, std::vector<std::filesystem::path>> s_FileRepository;
};