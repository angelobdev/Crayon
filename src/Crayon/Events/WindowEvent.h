#pragma once

#include "Event.h"

namespace Crayon
{
    enum WindowState
    {
        Closed, Resized, Minimized, Focused, Unfocused
    };

    class WindowEvent : public Event
    {
    private:
        WindowState m_WindowState;

    public:
        explicit WindowEvent(WindowState state) : m_WindowState(state)
        { m_IsNull = false; }

         WindowState GetWindowState() const
        { return m_WindowState; }

        // Override
         std::string GetName() const override
        { return &"Window Event - STATE: "[m_WindowState]; }
    };

}