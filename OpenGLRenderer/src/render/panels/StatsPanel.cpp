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

	ImGui::Text("Draw Calls: %d", Stats::GetDrawCalls());

	ImGui::End();
}
