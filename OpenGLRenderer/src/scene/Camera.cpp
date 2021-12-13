#include <pch.h>
#include "Camera.h"
#include "Input.h"

Camera::Camera()
    : m_CameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_CameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_Yaw(-90.0f), m_Pitch(0.0f), m_Fov(45.0f), m_View(glm::mat4(1.0f)), m_Projection(glm::mat4(1.0f)), m_AspectRatio(800.0f/600.0f)
{
}

void Camera::Update(float deltaTime)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (Input::Keys[GLFW_KEY_W])
        m_CameraPos += cameraSpeed * m_CameraFront;
    if (Input::Keys[GLFW_KEY_S])
        m_CameraPos -= cameraSpeed * m_CameraFront;
    if (Input::Keys[GLFW_KEY_A])
        m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
    if (Input::Keys[GLFW_KEY_D])
        m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
    if (Input::Keys[GLFW_KEY_Z])
        m_CameraPos += m_CameraUp * cameraSpeed;
    if (Input::Keys[GLFW_KEY_X])
        m_CameraPos -= m_CameraUp * cameraSpeed;


    float cameraSensitivity = 2.5f * deltaTime;
    m_Yaw += Input::MouseOffset.x * cameraSensitivity;
    m_Pitch += Input::MouseOffset.y * cameraSensitivity;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(front);

    m_View = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
    m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, 0.03f, 1000.0f);
}

void Camera::OnScroll(float deltaTime, float scroll)
{
    m_Fov += scroll * deltaTime * 45.0f;
}
