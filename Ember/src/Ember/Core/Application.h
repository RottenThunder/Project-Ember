#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "DeltaTime.h"
#include "Ember/Events/EventSystem.h"
#include "Ember/ImGui/ImGuiLayer.h"

namespace Ember
{
	class EMBER_API Application
	{
	private:
		static Application* Instance;
		std::unique_ptr<Window> MainWindow;
		ImGuiLayer* imguiLayer;
		bool Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack layerStack;
		long double LastFrameTime = 0.0f;
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		inline Window& GetWindow() { return *MainWindow; }

		inline static Application& Get() { return *Instance; }
	};

	Application* CreateApplication();
}