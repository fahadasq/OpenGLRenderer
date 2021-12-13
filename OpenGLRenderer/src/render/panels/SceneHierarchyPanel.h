#pragma once

#include <3rdparty/imgui/imgui.h>
#include <render/SceneView.h>

class SceneHierarchyPanel
{
public:
	SceneHierarchyPanel();

	void Render(SceneView* m_Sceneview);
};

