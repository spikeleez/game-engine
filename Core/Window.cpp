#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

GameEngine::Core::Window::Window(const WindowProps& Props)
{
    Init(Props);
}

GameEngine::Core::Window::~Window()
{
    Shutdown();
}

void GameEngine::Core::Window::Init(const WindowProps& Props)
{
    Data.Title = Props.Title;
    Data.Width = Props.Width;
    Data.Height = Props.Height;

    if (!glfwInit())
    {
        throw std::runtime_error("GLFW: failed to initialize.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    NativeWindow = glfwCreateWindow((int)Data.Width, (int)Data.Height, Data.Title.c_str(), nullptr, nullptr);

    if (!NativeWindow)
    {
        throw std::runtime_error("GLFW: failed to create window.");
    }

    glfwMakeContextCurrent(NativeWindow);
    glfwSwapInterval(1); // VSync.

    // Center window on primary monitor
    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* VideoMode = glfwGetVideoMode(PrimaryMonitor);

    const int PosX = (VideoMode->width - (int)Data.Width) / 2;
    const int PosY = (VideoMode->height - (int)Data.Height) / 2;

    glfwSetWindowPos(NativeWindow, PosX, PosY);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("GLAD: failed to initialize OpenGL context.");
    }

    glfwSetWindowUserPointer(NativeWindow, &Data);

    glfwSetWindowCloseCallback(NativeWindow, [](GLFWwindow* W)
    {
        const auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(W));
        Events::Application::WindowCloseEvent Event;
        Data.EventCallback(Event);
    });

    glfwSetWindowSizeCallback(NativeWindow, [](GLFWwindow* W, int Width, int Height)
    {
        const auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(W));
        Events::Application::WindowResizeEvent Event(Width, Height);
        Data.EventCallback(Event);
    });

    glfwSetKeyCallback(NativeWindow, [](GLFWwindow* W, int Key, int, int Action, int)
    {
        const auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(W));
        switch (Action)
        {
        case GLFW_PRESS: { Events::Keys::KeyPressedEvent Event(Key, false); Data.EventCallback(Event); break; }
        case GLFW_RELEASE: { Events::Keys::KeyPressedEvent Event(Key, false); Data.EventCallback(Event); break; }
        case GLFW_REPEAT: {Events::Keys::KeyPressedEvent Event(Key, true); Data.EventCallback(Event); break; }
        }
    });

    glfwSetCursorPosCallback(NativeWindow, [](GLFWwindow* W, double X, double Y)
    {
        const auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(W));
        Events::Mouse::MouseMoveEvent Event((float)X, (float)Y);
        Data.EventCallback(Event);
    });
}

void GameEngine::Core::Window::Shutdown()
{
    glfwDestroyWindow(NativeWindow);
    glfwTerminate();
}

void GameEngine::Core::Window::Tick()
{
    glfwPollEvents();
    glfwSwapBuffers(NativeWindow);
}

bool GameEngine::Core::Window::ShouldClose() const
{
    return glfwWindowShouldClose(NativeWindow);
}
