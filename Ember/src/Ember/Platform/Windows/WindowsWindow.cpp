#include "empch.h"
#include "WindowsWindow.h"
#ifdef EM_PLATFORM_WINDOWS
#include "Ember/Events/EventSystem.h"
#include "Ember/Platform/OpenGL/OpenGLContext.h"

namespace Ember
{
	static bool GLFWInitialized = false;

	static void GLFWerrorCallback(int32_t error, const char* description)
	{
		EM_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Terminate();
	}

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		windowData.Title = props.Title;
		windowData.Width = props.Width;
		windowData.Height = props.Height;

		EM_LOG_INFO("Creating Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!GLFWInitialized)
		{
			int32_t glfwStatus = glfwInit();
			EM_FATAL_ASSERT(glfwStatus, "Failed to intialize GLFW!!!");

			glfwSetErrorCallback(GLFWerrorCallback);
			GLFWInitialized = true;
		}

		window = glfwCreateWindow(props.Width, props.Height, windowData.Title.c_str(), NULL, NULL);

		context = new OpenGLContext(window);
		context->Init();

		glfwSetWindowUserPointer(window, &windowData);
		SetVSync(false);

		// Setting Event Callbacks (GLFW)
		glfwSetWindowSizeCallback(window, [](GLFWwindow* _window, int32_t width, int32_t height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* _window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* _window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(window, [](GLFWwindow* _window, uint32_t keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* _window, int32_t button, int32_t action, int32_t mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* _window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);
				MouseScrolledEvent event((float_t)xOffset, (float_t)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* _window, double xPosition, double yPosition)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_window);
				MouseMovedEvent event((float_t)xPosition, (float_t)yPosition);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Terminate()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		windowData.VSync = enable;
	}

	bool WindowsWindow::IsVSync() const
	{
		return windowData.VSync;
	}
}
#endif // EM_PLATFORM_WINDOWS