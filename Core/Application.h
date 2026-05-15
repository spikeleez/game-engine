#pragma once

#include "Window.h"
#include <memory>
#include "Events/ApplicationEvents.h"

namespace GameEngine::Core
{
    class Application
    {
    public:
        explicit Application(const WindowProps& Props = WindowProps());
        virtual ~Application() = default;

        void Run();
        void Shutdown();

        Window& GetWindow() { return *AppWindow; }

        static Application& Get() { return *Instance; }

    protected:
        virtual void BeginPlay();
        virtual void Tick(float DeltaTime) {}
        virtual void Render() {}
        virtual void OnEvent(Event& Event);

        virtual bool OnWindowClose(Events::Application::WindowCloseEvent& Event);

    private:
        std::unique_ptr<Window> AppWindow;
        bool bIsRunning = true;

        static Application* Instance;
    };
}
