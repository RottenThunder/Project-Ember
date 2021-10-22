#pragma once
#include "Core.h"
#include "Window.h"
#include "Ember/Events/EventSystem.h"

namespace Ember
{
	class EMBER_API Application
	{
	private:
		std::unique_ptr<Window> MainWindow;
		bool Running = true;
	public:
		Application();
		~Application();

		void Run();
	};

	Application* CreateApplication();
}