#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Ember/Events/EventSystem.h"
#include "Ember/Platform/OpenGL/Shader.h"

namespace Ember
{
	class EMBER_API Application
	{
	private:
		static Application* Instance;
		std::unique_ptr<Window> MainWindow;
		bool Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack layerStack;

		uint32_t VertexArray, VertexBuffer, IndexBuffer;
		std::unique_ptr<Shader> shader;
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