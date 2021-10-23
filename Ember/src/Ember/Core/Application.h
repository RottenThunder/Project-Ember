#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Ember/Events/EventSystem.h"

namespace Ember
{
	class EMBER_API Application
	{
	private:
		std::unique_ptr<Window> MainWindow;
		bool Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack layerStack;
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	};

	Application* CreateApplication();
}