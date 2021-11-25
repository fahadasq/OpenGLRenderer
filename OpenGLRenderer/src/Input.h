#pragma once

#include <pch.h>

enum class EInputButton
{
	Left = 0,
	Right = 1,
	Middle = 2,
	None = 9
};

static class Input
{
public:
	static bool Keys[1024];
	static glm::vec2 MousePos;
	static glm::vec2 MouseOffset;
	static float ScrollOffset;

	static void KeyCallback(int key, int scancode, int action, int mode);
	static void ScrollCallback(double xoffset, double yoffset);
	static void MouseCallback(double xpos, double ypos);
	static EInputButton GetPressedButton(GLFWwindow* window)
	{
		if (glfwGetMouseButton(window, 0) == GLFW_PRESS)
			return EInputButton::Left;
		else if (glfwGetMouseButton(window, 1) == GLFW_PRESS)
			return EInputButton::Right;
		else if (glfwGetMouseButton(window, 2) == GLFW_PRESS)
			return EInputButton::Middle;

		return EInputButton::None;
	}

private:
	Input() { }
};