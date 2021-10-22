#include "empch.h"
#include "WindowsWindow.h"

namespace Ember
{
#ifdef EM_PLATFORM_WINDOWS

	static bool GLFWInitialized = false;

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
			int success = glfwInit();
			EM_FATAL_ASSERT(success, "Could not intialize GLFW!");

			GLFWInitialized = true;
		}

		window = glfwCreateWindow(props.Width, props.Height, windowData.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &windowData);
		SetVSync(true);
	}

	void WindowsWindow::Terminate()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
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

#endif // EM_PLATFORM_WINDOWS
}