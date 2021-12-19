#pragma once

#include <render/SceneView.h>
#include <3rdparty/imgui/imgui.h>

class InspectorPanel
{
public:
	InspectorPanel();

	void Render(SceneView* m_Sceneview);
private:
	void DisplayUniformVariable(char* buffer, Uniform& uniform);
	void DisplayTextureUniform(TextureUniform& uniform);
	void DisplayObjectInfo(GameObject* object);
};

