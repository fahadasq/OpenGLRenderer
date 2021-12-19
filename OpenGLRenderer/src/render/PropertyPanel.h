#pragma once

#include <3rdparty/imgui/imgui.h>
#include "SceneView.h"
#include "panels/SceneHierarchyPanel.h"
#include "panels/InspectorPanel.h"
#include "panels/ContentBrowserPanel.h"
#include "panels/StatsPanel.h"
#include <functional>

class EditorView
{
public:

	EditorView()
	{
		m_InspectorPanel = std::make_unique<InspectorPanel>();
		m_HierarchyPanel = std::make_unique<SceneHierarchyPanel>();
		m_ContentPanel = std::make_unique<ContentBrowserPanel>();
		m_StatsPanel = std::make_unique<StatsPanel>();
	}

	void Render(SceneView* m_Scene);


private:
	std::unique_ptr<InspectorPanel> m_InspectorPanel;
	std::unique_ptr<SceneHierarchyPanel> m_HierarchyPanel;
	std::unique_ptr<ContentBrowserPanel> m_ContentPanel;
	std::unique_ptr<StatsPanel> m_StatsPanel;
};