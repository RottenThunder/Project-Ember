#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Ember/Events/EventSystem.h"
#include "Ember/Renderer/Shader.h"
#include "Ember/Renderer/Buffer.h"
#include "Ember/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		std::shared_ptr<VertexArray> squareVertexArray;
		std::shared_ptr<Shader> shaderSquare;
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