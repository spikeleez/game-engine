#pragma once

#include "Event.h"

namespace GameEngine::Events::Mouse
{
    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(float X, float Y)
            : X(X)
            , Y(Y)
        {}

        [[nodiscard]]float GetX() const { return X; }
        [[nodiscard]]float GetY() const { return Y; }

        EVENT_TYPE(MouseMoved)
        EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse)

    private:
        float X, Y;
    };

    class MouseButtonEvent : public Event
    {
    public:
        int GetButton() const { return Button; }
        EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse)

    protected:
        explicit MouseButtonEvent(int Button)
            : Button(Button)
        {}

        int Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(int Button)
            : MouseButtonEvent(Button)
        {}

        EVENT_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleasedEvent(int Button)
            : MouseButtonEvent(Button)
        {}

        EVENT_TYPE(MouseButtonReleased)
    };
}
