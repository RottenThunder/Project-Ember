#include "empch.h"
#include "Application.h"
#include <GLFW/glfw3.h> // For Testing

namespace Ember
{
	Application::Application()
	{
		MainWindow = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication))
		{
			EM_LOG_TRACE(event);
		}
		if (event.IsInCategory(EventCategoryInput))
		{
			EM_LOG_TRACE(event);
		}

		while (Running)
		{
			glClearColor(0.9412f, 0.3686f, 0.1059f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			MainWindow->OnUpdate();
		}
	}
}