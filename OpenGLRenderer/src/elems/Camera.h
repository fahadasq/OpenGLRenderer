#pragma once

#include <pch.h>

class Camera
{
private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;

	float m_Yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float m_Pitch;
	float m_Fov;

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	float m_AspectRatio;

public:
	Camera();

	void Update(float deltaTime);

	void OnScroll(float deltaTime, float scroll);

	const glm::vec3& GetCameraPos() const { return m_CameraPos; }
	const glm::mat4& GetViewMatrix() const { return m_View; }
	const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
	void SetAspectRatio(float aspect) { m_AspectRatio = aspect; }
};