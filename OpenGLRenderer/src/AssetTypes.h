#pragma once

#include "UUID.h"
#include <yaml-cpp/yaml.h>

enum class AssetType
{
	None = 0,
	Texture2D = 1,
	Mesh = 2,
	Material = 3
};

struct Asset
{
protected:
	UniversallyUniqueID m_UUID;
	std::string m_SourceFilePath;
	AssetType m_Type;

public:
	Asset() : m_UUID(), m_SourceFilePath(), m_Type(AssetType::None) { }
	Asset(const char* source) : m_UUID(), m_SourceFilePath(source), m_Type(AssetType::None) { }

	const uint64_t GetID() const { return m_UUID; }
	const std::string GetSourcePath() const { return m_SourceFilePath; }

	void Serialize(const char* filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
	
		out << YAML::Key << "UUID" << YAML::Value << (uint64_t)m_UUID;
		out << YAML::Key << "Source Path" << YAML::Value << m_SourceFilePath;
		out << YAML::Key << "Asset Type" << YAML::Value << (int)m_Type;

		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}
	bool Deserialize(const char* filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		if (!data["UUID"])
			return false;

		if (!data["Source Path"])
			return false;

		if (!data["Asset Type"])
			return false;

		UniversallyUniqueID uuid = data["UUID"].as<uint64_t>();
		std::string srcPath = data["Source Path"].as<std::string>();
		int type = data["Asset Type"].as<int>();

		m_UUID = uuid;
		m_SourceFilePath = srcPath;
		m_Type = (AssetType)type;

		return true;
	}

	static uint64_t DeserializeID(const char* filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		uint64_t id = data["UUID"].as<uint64_t>();

		return id;
	}
};

struct ShaderAsset
{
protected:
	UniversallyUniqueID m_UUID;
	std::string m_vSourceFilePath;
	std::string m_fSourceFilePath;
	std::string m_gSourceFilePath;

public:
	ShaderAsset(uint64_t id, const char* vSource, const char* fSource, const char* gSource = nullptr)
		: m_UUID(id), m_vSourceFilePath(vSource),
		m_fSourceFilePath(fSource), m_gSourceFilePath(gSource) { }
	ShaderAsset(const char* vSource, const char* fSource, const char* gSource = nullptr)
		: m_UUID(), m_vSourceFilePath(vSource), m_fSourceFilePath(fSource),
		m_gSourceFilePath(gSource) { }
	ShaderAsset()
		: m_UUID(), m_vSourceFilePath(), m_fSourceFilePath(),
		m_gSourceFilePath() { }

	const uint64_t GetID() const { return m_UUID; }
	std::string GetVertSourcePath() const { return m_vSourceFilePath; }
	std::string GetFragSourcePath() const { return m_fSourceFilePath; }
	std::string GetGeoSourcePath() const { return m_gSourceFilePath; }

	void Serialize(const char* filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;

		out << YAML::Key << "UUID" << YAML::Value << (uint64_t)m_UUID;
		out << YAML::Key << "Vertex Source Path" << YAML::Value << m_vSourceFilePath;
		out << YAML::Key << "Fragment Source Path" << YAML::Value << m_fSourceFilePath;
		//out << YAML::Key << "Geometry Source Path" << YAML::Value << m_gSourceFilePath;

		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}
	bool Deserialize(const char* filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		if (!data["UUID"])
			return false;

		if (!data["Vertex Source Path"])
			return false;

		if (!data["Fragment Source Path"])
			return false;

		/*if (!data["Geometry Source Path"])
			return false;*/

		UniversallyUniqueID uuid = data["UUID"].as<uint64_t>();
		std::string vSrcPath = data["Vertex Source Path"].as<std::string>();
		std::string fSrcPath = data["Fragment Source Path"].as<std::string>();
		//std::string gSrcPath = data["Geometry Source Path"].as<std::string>();


		m_UUID = uuid;
		m_vSourceFilePath = vSrcPath;
		m_fSourceFilePath = fSrcPath;
		m_gSourceFilePath = std::string();

		std::cout << "Deserialized Vertex: " << m_vSourceFilePath << "\n";

		return true;
	}

	static uint64_t DeserializeID(const char* filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		uint64_t id = data["UUID"].as<uint64_t>();

		return id;
	}
};
