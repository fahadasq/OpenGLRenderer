#pragma once

#include <3rdparty/imgui/imgui.h>
#include "SceneView.h"
#include <functional>

class PropertyPanel
{
public:

	PropertyPanel()
	{

	}

	void Render(SceneView* m_Scene);

	void SetMeshCallbackFunction(const std::function<void(const std::string&)>& callback)
	{
		m_SetMeshCallback = callback;
	}

private:
	std::function<void(const std::string&)> m_SetMeshCallback;
};