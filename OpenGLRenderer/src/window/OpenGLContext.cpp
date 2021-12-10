#include <pch.h>
#include "OpenGLContext.h"
#include <ErrorHandler.h>

static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
    pWindow->OnKey(key, scancode, action, mods);
}

static void on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
    pWindow->OnScroll(xoffset, yoffset);
}

static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
    auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
    pWindow->OnResize(width, height);
}


static void on_window_close_callback(GLFWwindow* window)
{
    IWindow* pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
    pWindow->OnClose();
}


bool OpenGLContext::Init(IWindow* window)
{
    __super::Init(window);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto glWindow = glfwCreateWindow(window->Width, window->Height, window->Title.c_str(), glfwGetPrimaryMonitor(), NULL);
    window->SetNativeWindow(glWindow);

    if (glWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwSetWindowUserPointer(glWindow, window);
    glfwSetKeyCallback(glWindow, on_key_callback);
    glfwSetScrollCallback(glWindow, on_scroll_callback);
    glfwSetWindowSizeCallback(glWindow, on_window_size_callback);
    glfwSetWindowCloseCallback(glWindow, on_window_close_callback);
    glfwMakeContextCurrent(glWindow);
    glfwSwapInterval(1);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    
    glEnable(GL_DEPTH_TEST);

    return true;
}

void OpenGLContext::PreRender()
{
    GLCall(glViewport(0, 0, m_Window->Width, m_Window->Height));
    GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void OpenGLContext::PostRender()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow*)m_Window->GetNativeWindow());
}

void OpenGLContext::End()
{
    glfwDestroyWindow((GLFWwindow*)m_Window->GetNativeWindow());
    glfwTerminate();
}
