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

		vertexArray.reset(VertexArray::Create());

		float_t vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout =
		{
			{ ShaderDataType::Vec3, "a_Position", false },
			{ ShaderDataType::Vec4, "a_Colour", false }
		};

		vertexBuffer->SetLayout(layout);

		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec3 v_Position;
			in vec4 v_Colour;

			void main()
			{
				Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
				Colour = v_Colour;
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));



		// Square

		squareVertexArray.reset(VertexArray::Create());

		float_t SquareVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f, //Bottom-Left
			0.75f, -0.75f, 0.0f, //Bottom-Right
			-0.75f, 0.75f, 0.0f, //Top-Left
			0.75f, 0.75f, 0.0f //Top-Right
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

		squareVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3, "a_Position", false }
			});

		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 3, 2, 0, 0, 1, 3 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrcSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec3 v_Position;
			in vec4 v_Colour;

			void main()
			{
				Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		shaderSquare.reset(new Shader(vertexSrcSquare, fragmentSrcSquare));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (Running)
		{
			//glClearColor(0.9412f, 0.3686f, 0.1059f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);

			shaderSquare->Bind();
			squareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, squareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			shader->Bind();
			vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack)
				layer->OnUpdate();

			MainWindow->OnUpdate();
		}
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