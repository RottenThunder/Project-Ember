#include <Ember.h>

class NewLayer : public Ember::Layer
{
private:
	//---SQUARE-----------------------------------------
	std::shared_ptr<Ember::VertexArray> squareVertexArray;
	std::shared_ptr<Ember::VertexBuffer> squareVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> squareIndexBuffer;
	std::shared_ptr<Ember::Shader> squareShader;
	//--------------------------------------------------

	//---TRIANGLE---------------------------------------
	std::shared_ptr<Ember::VertexArray> triangleVertexArray;
	std::shared_ptr<Ember::VertexBuffer> triangleVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> triangleIndexBuffer;
	std::shared_ptr<Ember::Shader> triangleShader;
	//--------------------------------------------------
public:
	NewLayer()
		: Layer("Example")
	{

		//---SQUARE-----------------------------------------

		squareVertexArray.reset(Ember::VertexArray::Create());

		float_t SquareVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f, //Bottom-Left
			0.75f, -0.75f, 0.0f, //Bottom-Right
			-0.75f, 0.75f, 0.0f, //Top-Left
			0.75f, 0.75f, 0.0f //Top-Right
		};

		squareVertexBuffer.reset(Ember::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

		squareVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false }
			});

		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 3, 2, 0, 0, 1, 3 };
		squareIndexBuffer.reset(Ember::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

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

		squareShader.reset(new Ember::Shader(vertexSrcSquare, fragmentSrcSquare));

		//--------------------------------------------------



		//---TRIANGLE---------------------------------------

		triangleVertexArray.reset(Ember::VertexArray::Create());

		float_t TriangleVertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f, //Bottom-Left
			0.5f, -0.5f, 0.0f, //Bottom-Right
			0.0f, 0.5f, 0.0f //Top
		};

		triangleVertexBuffer.reset(Ember::VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices)));

		triangleVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false }
			});

		triangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		triangleIndexBuffer.reset(Ember::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

		triangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

		std::string vertexSrcTriangle = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcTriangle = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			void main()
			{
				Colour = vec4(1.0, 0.0, 0.0, 1.0);
			}
		)";

		triangleShader.reset(new Ember::Shader(vertexSrcTriangle, fragmentSrcTriangle));

		//--------------------------------------------------
	}

	void OnUpdate() override
	{
		Ember::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ember::RenderCommand::Clear();

		Ember::Renderer::BeginScene();

		squareShader->Bind();
		Ember::Renderer::Submit(squareVertexArray);

		triangleShader->Bind();
		Ember::Renderer::Submit(triangleVertexArray);

		Ember::Renderer::EndScene();
	}

	void OnEvent(Ember::Event& event) override
	{
		if (event.GetEventType() == Ember::EventType::KeyPressed)
		{
			Ember::KeyPressedEvent& e = (Ember::KeyPressedEvent&)event;
			EM_LOG_WARN("{0}", char(e.GetKeyCode()));
		}
	}
};

class GameApplication : public Ember::Application
{
public:
	GameApplication()
	{
		PushLayer(new NewLayer);
	}

	~GameApplication()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new GameApplication();
}