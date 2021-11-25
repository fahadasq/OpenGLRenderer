#include <pch.h>
#include "Input.h"


void GetMouseOffset(double xpos, double ypos);

bool Input::Keys[1024];
glm::vec2 Input::MousePos;
glm::vec2 Input::MouseOffset;
float Input::ScrollOffset;

float lastX = 0.0f;
float lastY = 0.0f;
bool firstMouse = true;

void Input::KeyCallback(int key, int scancode, int action, int mode)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Input::Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Input::Keys[key] = false;
    }
}

void Input::MouseCallback(double xpos, double ypos)
{    
    Input::MousePos = glm::vec2(xpos, ypos);
    GetMouseOffset(xpos, ypos);
}

void GetMouseOffset(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    Input::MouseOffset = glm::vec2(xpos - lastX, lastY - ypos);

    lastX = (float)xpos;
    lastY = (float)ypos;
}

void Input::ScrollCallback(double xoffset, double yoffset)
{
    Input::ScrollOffset = (float)yoffset;
}