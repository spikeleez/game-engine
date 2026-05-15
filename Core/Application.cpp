#include "Application.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace GameEngine::Core
{
    Application* Application::Instance = nullptr;
}

GameEngine::Core::Application::Application(const WindowProps& Props)
{
    Instance = this;
    AppWindow = std::make_unique<Window>(Props);
    AppWindow->SetEventCallback(EVENT_BIND(OnEvent));
}

void GameEngine::Core::Application::OnEvent(Event& Event)
{
    EventDispatcher Dispatcher(Event);
    Dispatcher.Dispatch<Events::Application::WindowCloseEvent>(EVENT_BIND(OnWindowClose));
}

bool GameEngine::Core::Application::OnWindowClose(Events::Application::WindowCloseEvent& Event)
{
    bIsRunning = false;
    return true;
}

void GameEngine::Core::Application::Run()
{
    float LastTime = 0.0f;

    BeginPlay();

    while (bIsRunning && !AppWindow->ShouldClose())
    {
        const float CurrentTime = static_cast<float>(glfwGetTime());
        const float DeltaTime = CurrentTime - LastTime;
        LastTime = CurrentTime;

        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Tick(DeltaTime);
        Render();

        AppWindow->Tick();
    }
}

void GameEngine::Core::Application::Shutdown()
{
    bIsRunning = false;
}

void GameEngine::Core::Application::BeginPlay()
{
    std::cout << "Application Started!";
}
