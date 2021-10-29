#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Ember/Events/EventSystem.h"
#include "Ember/Renderer/Shader.h"
#include "Ember/Renderer/Buffer.h"

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

		uint32_t VertexArray;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<IndexBuffer> indexBuffer;
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