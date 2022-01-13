#pragma once

#include <render/SceneView.h>
#include <3rdparty/imgui/imgui.h>
#include "AssetFilePanel.h"

class InspectorPanel
{
public:
	InspectorPanel();

	std::unique_ptr<AssetFilePanel> m_FilePanel;

	void Render(SceneView* m_Sceneview);
private:
	void DisplayUniformVariable(char* buffer, Uniform& uniform);
	void DisplayTextureUniform(TextureUniform& uniform, std::shared_ptr<Texture2D>& texture);
	void DisplayObjectInfo(GameObject* object);
};

