#pragma once

#include "Event.h"

namespace GameEngine::Events::Keys
{
    class KeyEvent : public Event
    {
    public:
        int GetKeyCode() const { return KeyCode; }
        EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

    protected:
        explicit KeyEvent(int KeyCode)
            : KeyCode(KeyCode)
        {}

        int KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int KeyCode, bool bRepeat = false)
            : KeyEvent(KeyCode), bRepeat(bRepeat)
        {}

        bool IsRepeat() const { return bRepeat; }

        EVENT_TYPE(KeyPressed)

    private:
        bool bRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(int KeyCode)
            : KeyEvent(KeyCode)
        {}

        EVENT_TYPE(KeyReleased)
    };
}
