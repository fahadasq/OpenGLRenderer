#pragma once

struct ViewProjection {
	glm::mat4 view;
	glm::mat4 projection;

	static const unsigned int slot = 0;
	static const char* GetName()
	{
		const char* name = "ViewProjection";
		return name;
	}
};