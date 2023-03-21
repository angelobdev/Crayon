#include "Window.h"

namespace Crayon
{
	Window::Window(const char* title, int width, int height)
		: m_HasBeenClosed(false), m_IsFullscreen(false), m_WindowedWidth(width), m_WindowedHeight(height)
	{
		// ----- INITIALIZING WINDOWING SYSTEM -----

		// GLFW
		if (!glfwInit())
		{
			CRAYON_CORE_ERROR("Failed to initialize the window!");
			exit(-1);
		}

		// Hints
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Creating window
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_Window)
		{
			CRAYON_CORE_ERROR("Failed to create the window!");
			exit(-1);
		}

		// Centering window
		int xpos, ypos;
		GetCenteredPosition(width, height, &xpos, &ypos);
		glfwSetWindowPos(m_Window, xpos, ypos);

		// ----- SETTING CALLBACKS -----

		// Key Callbacks
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Key k = key;
				KeyState kState{ NoKState };

				switch (action)
				{
				case GLFW_PRESS:
					kState = KeyState::Touched;
					break;
				case GLFW_REPEAT:
					kState = KeyState::Pressed;
					break;
				case GLFW_RELEASE:
					kState = KeyState::Released;
					break;
				default:
					CRAYON_CORE_ERROR("Invalid Key Action (GLFW Key Callback)");
					break;
				}

				EventDispatcher::Dispatch(new KeyEvent(k, kState)); // new Event will be deleted by Application::OnEvent()
			}
		);

		// Mouse Movement Callbacks
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				EventDispatcher::Dispatch(new MouseMovedEvent(xpos, ypos));
			}
		);

		// Mouse Button Callbacks
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				MouseButton mbutton{ NoButton };
				MouseButtonState mstate{ NoBState };

				switch (button)
				{
				case GLFW_MOUSE_BUTTON_LEFT:
					mbutton = MouseButton::Left;
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					mbutton = MouseButton::Middle;
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					mbutton = MouseButton::Right;
					break;
				default:
					CRAYON_CORE_ERROR("Invalid Mouse Button");
					break;
				}

				switch (action)
				{
				case GLFW_PRESS:
					mstate = MouseButtonState::Clicked;
					break;
				case GLFW_RELEASE:
					mstate = MouseButtonState::Unclicked;
					break;
				default:
					CRAYON_CORE_ERROR("Invalid Mouse Button State");
					break;
				}

				EventDispatcher::Dispatch(new MouseButtonEvent(mbutton, mstate));
			}
		);

		// Window Closed Callback
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				EventDispatcher::Dispatch(new WindowEvent(WindowState::Closed));
			}
		);

		// Window Resized
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				EventDispatcher::Dispatch(new WindowEvent(WindowState::Resized));
			}
		);

		// Window Minimized
		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified)
			{
				if (iconified)
					EventDispatcher::Dispatch(new WindowEvent(WindowState::Minimized));
			}
		);

		// Window Focused, Unfocused
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
			{
				WindowState focus = focused ? WindowState::Focused : WindowState::Unfocused;
				EventDispatcher::Dispatch(new WindowEvent(focus));
			}
		);

		// ----- SETTING OPENGL -----
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGL())
		{
			CRAYON_CORE_ERROR("Failed to initialize OpenGL!");
			exit(-1);
		}

	}

	void Window::Close()
	{
		if (!this->m_HasBeenClosed)
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
			this->m_HasBeenClosed = true;
		}
	}

	void Window::ToggleFullscreen()
	{
		// Inverting flag
		this->m_IsFullscreen = !this->m_IsFullscreen;

		if (this->m_IsFullscreen)
		{ // GOING FULLSCREEN

			// Saving old size
			m_WindowedWidth = this->GetWidth();
			m_WindowedHeight = this->GetHeight();

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_Window, monitor, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
		}
		else
		{ // GOING WINDOWED
			int xpos, ypos;
			GetCenteredPosition(m_WindowedWidth, m_WindowedHeight, &xpos, &ypos);
			glfwSetWindowMonitor(m_Window, NULL, xpos, ypos, m_WindowedWidth, m_WindowedHeight, GLFW_DONT_CARE);
		}

	}

	void Window::GetCenteredPosition(int width, int height, int* xpos, int* ypos)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		*xpos = vidmode->width / 2 - width / 2;
		*ypos = vidmode->height / 2 - height / 2;
	}
}