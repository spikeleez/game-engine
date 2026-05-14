#pragma once

#include <string>
#include <functional>

namespace GameEngine
{
    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        KeyPressed,
        KeyReleased,
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased
    };

    enum EventCategory
    {
        EventCategoryNone = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput = 1 << 1,
        EventCategoryKeyboard = 1 << 2,
        EventCategoryMouse = 1 << 3,
    };

#define EVENT_TYPE(Type) \
    static EventType GetStaticType() { return EventType::Type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #Type; }

#define EVENT_CATEGORY(Category) \
    virtual int GetCategoryFlags() const override { return Category; }

    class Event
    {
    public:
        virtual ~Event() = default;

        [[nodiscard]]virtual EventType GetEventType() const = 0;
        [[nodiscard]]virtual const char* GetName() const = 0;
        [[nodiscard]]virtual int GetCategoryFlags() const = 0;
        [[nodiscard]]virtual std::string ToString() const { return GetName(); }

        [[nodiscard]]bool IsInCategory(const EventCategory Category) const
        {
            return GetCategoryFlags() & Category;
        }

        bool bHandled = false;
    };

    class EventDispatcher
    {
    public:
        explicit EventDispatcher(Event& InEvent)
            : TargetEvent(InEvent)
        {}

        template<typename T>
        bool Dispatch(std::function<bool(T&)> Func)
        {
            if (TargetEvent.GetEventType() == T::GetStaticType())
            {
                TargetEvent.bHandled = Func(static_cast<T&>(TargetEvent));
                return true;
            }
            return false;
        }

    private:
        Event& TargetEvent;
    };

#define EVENT_BIND(fn) [this](auto&&... args) \
    -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
}
