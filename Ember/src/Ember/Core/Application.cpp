#include "empch.h"
#include "Application.h"
#include "Input.h"
#include "Ember/Renderer/Renderer.h"
#include <GLFW/glfw3.h> //TODO: Find a different way of getting the time than using glfwGetTime()

namespace Ember
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application()
	{
		EM_PROFILE_FUNCTION();

		EM_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		MainWindow = std::unique_ptr<Window>(Window::Create());
		MainWindow->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		Renderer::Init();

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
	}

	Application::~Application()
	{
		EM_PROFILE_FUNCTION();

		Renderer::Terminate();
	}

	void Application::Run()
	{
		EM_PROFILE_FUNCTION();

		while (Running)
		{
			EM_PROFILE_SCOPE("RunLoop");

			double time = glfwGetTime(); //TODO: Find Platform Specific Time Functions. For example, Windows = QueryPerformanceCounter()
			DeltaTime deltaTime = time - LastFrameTime;
			LastFrameTime = time;

			if (!Minimized)
			{
				{
					EM_PROFILE_SCOPE("LayerStatck OnUpdate");

					for (Layer* layer : layerStack)
						layer->OnUpdate(deltaTime);
				}

				imguiLayer->Begin();
				{
					EM_PROFILE_SCOPE("LayerStatck OnImGuiRender");

					for (Layer* layer : layerStack)
						layer->OnImGuiRender();
				}
				imguiLayer->End();
			}


			MainWindow->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		EM_PROFILE_FUNCTION();

		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		EM_PROFILE_FUNCTION();

		layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		EM_PROFILE_FUNCTION();

		layerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		EM_PROFILE_FUNCTION();

		layerStack.PopOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EM_PROFILE_FUNCTION();

		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));
		eventDispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResize));

		//EM_LOG_TRACE("{0}", e);

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		EM_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			Minimized = true;
			return false;
		}

		Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}