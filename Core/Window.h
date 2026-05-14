#pragma once

#include <functional>
#include <string>
#include "Events/Event.h"

struct GLFWwindow;

namespace GameEngine
{
    struct WindowProps
    {
        std::string Title;
        uint32_t    Width;
        uint32_t    Height;

        WindowProps(std::string Title = "Game Engine", uint32_t Width = 1280, uint32_t Height = 720)
            : Title(std::move(Title))
            , Width(Width)
            , Height(Height)
        {}
    };

    class Window
    {
    public:
        explicit Window(const WindowProps& Props);
        ~Window();

        void Tick();
        [[nodiscard]]bool ShouldClose() const;

        [[nodiscard]]uint32_t GetWidth() const { return Data.Width; }
        [[nodiscard]]uint32_t GetHeight() const { return Data.Height; }
        [[nodiscard]]GLFWwindow* GetNativeWindow() const { return NativeWindow; }

        using EventCallbackFn = std::function<void(Event&)>;
        void SetEventCallback(const EventCallbackFn& Callback) { Data.EventCallback = Callback; }

    private:
        void Init(const WindowProps& Props);
        void Shutdown();

        GLFWwindow* NativeWindow = nullptr;

        struct WindowData
        {
            std::string Title;
            uint32_t Width = 0;
            uint32_t Height = 0;

            EventCallbackFn EventCallback = nullptr;
        };

        WindowData Data;
    };
}
