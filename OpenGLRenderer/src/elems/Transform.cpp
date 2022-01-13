#include "pch.h"

#include "Transform.h"

Transform::Transform()
	: m_Model(glm::mat4(1.0f)), m_Position(glm::vec3(1.0f)), m_Rotation(glm::vec3(0.0f)), m_Scale(glm::vec3(1.0f))
{
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_Position);	
	
	glm::quat quat;

	quat = glm::quat(glm::radians(m_Rotation));
	glm::mat4 rotationMatrix = glm::toMat4(quat);

	model *= rotationMatrix;

	model = glm::scale(model, m_Scale);
	m_Model = model;
}

Transform::~Transform()
{
	
}

void Transform::Update()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_Position);
	glm::quat quat;

	quat = glm::quat(glm::radians(m_Rotation));
	glm::mat4 rotationMatrix = glm::toMat4(quat);

	model *= rotationMatrix;

	model = glm::scale(model, m_Scale);
	m_Model = model;
	m_Quat = quat;
}
