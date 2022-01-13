#pragma once
class Transform
{
private:
	glm::mat4 m_Model;
	glm::quat m_Quat;
public:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	Transform();
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Transform();

	void Update();
	const glm::mat4& GetModel() { return m_Model; }
};

