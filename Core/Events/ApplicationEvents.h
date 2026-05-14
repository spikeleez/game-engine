#pragma once

#include "Event.h"

namespace GameEngine::Events::Application
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_TYPE(WindowClose)
        EVENT_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t Width, uint32_t Height)
            : Width(Width)
            , Height(Height)
        {}

        [[nodiscard]]uint32_t GetWidth() const { return Width; }
        [[nodiscard]]uint32_t GetHeight() const { return Height; }

        EVENT_TYPE(WindowResize)
        EVENT_CATEGORY(EventCategoryApplication)

    private:
        uint32_t Width, Height;
    };
}
