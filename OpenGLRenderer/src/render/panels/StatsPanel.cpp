#include "pch.h"
#include "StatsPanel.h"

#include <Stats.h>
#include <3rdparty/imgui/imgui.h>

#include <ResourceManager.h>

StatsPanel::StatsPanel()
{
}

void StatsPanel::Render()
{
	ImGui::Begin("Stats");

	std::stringstream ss;

	for (const auto& iter : ResourceManager::m_AssetRepository)
	{
		ss << "Asset ID: " << iter.second.GetID() << "\n";
		ss << "Asset Source Path: " << iter.second.GetSourcePath() << "\n";
	}

	ImGui::Text("Draw Calls: %d", Stats::GetDrawCalls());
	ImGui::Text(ss.str().c_str());

	ImGui::End();
}
