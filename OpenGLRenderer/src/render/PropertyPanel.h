#pragma once

#include <3rdparty/imgui/imgui.h>
#include "SceneView.h"
#include "panels/SceneHierarchyPanel.h"
#include "panels/InspectorPanel.h"
#include <functional>

class EditorView
{
public:

	EditorView()
	{
		m_InspectorPanel = std::make_unique<InspectorPanel>();
		m_HierarchyPanel = std::make_unique<SceneHierarchyPanel>();
	}

	void Render(SceneView* m_Scene);


private:
	std::unique_ptr<InspectorPanel> m_InspectorPanel;
	std::unique_ptr<SceneHierarchyPanel> m_HierarchyPanel;
};