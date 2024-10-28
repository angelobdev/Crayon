#pragma once

namespace Crayon::Events
    {
        enum WindowState
        {
            Closed,
            Resized,
            Minimized,
            Focused,
            Unfocused
        };

        struct WindowEvent
        {
        private:
            const WindowState m_State;

        public:
            WindowEvent(WindowState state)
                : m_State(state) {}

            const WindowState GetState() const
            {
                return m_State;
            }
        };
    }

