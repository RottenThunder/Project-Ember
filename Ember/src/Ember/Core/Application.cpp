#include "empch.h"
#include "Application.h"

namespace Ember
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		MainWindow = std::unique_ptr<Window>(Window::Create());
		MainWindow->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		EM_LOG_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (Running)
		{
			MainWindow->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Running = false;
		return true;
	}
}