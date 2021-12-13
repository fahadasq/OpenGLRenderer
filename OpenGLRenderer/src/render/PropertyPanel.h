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


private:
	void DisplayUniformVariable(char* buffer, Uniform& uniform);
	void DisplayTextureUniform(TextureUniform& uniform);
	void DisplayObjectInfo(GameObject* object);
};