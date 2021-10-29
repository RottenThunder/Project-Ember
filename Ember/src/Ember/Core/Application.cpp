#include "empch.h"
#include "Application.h"
#include "Input.h"
#include <glad/glad.h>

namespace Ember
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application()
	{
		EM_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		MainWindow = std::unique_ptr<Window>(Window::Create());
		MainWindow->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		float_t vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float_t), nullptr);

		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec3 v_Position;

			void main()
			{
				Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (Running)
		{
			glClearColor(0.9412f, 0.3686f, 0.1059f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack)
				layer->OnUpdate();

			MainWindow->OnUpdate();
		}

		shader->UnBind();
		vertexBuffer->UnBind();
		indexBuffer->UnBind();
		glDeleteVertexArrays(1, &VertexArray);
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		layerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		layerStack.PopOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

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
}