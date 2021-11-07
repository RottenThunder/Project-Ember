#include <Ember.h>
#include "Grid.h"
#include "PlayerPos.h"

class ExampleLayer : public Ember::Layer
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

	//---CAMERA-----------------------------------------
	Ember::OrthographicCamera OrthoCamera;
	//--------------------------------------------------
public:
	ExampleLayer()
		: Layer("Example"), OrthoCamera(-1.6f, 1.6f, -0.9f, 0.9f)
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

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

	void OnUpdate(Ember::DeltaTime DT) override
	{
		EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

		Ember::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ember::RenderCommand::Clear();

		OrthoCamera.SetPosition({ 0.5f, 0.5f, 0.0f });
		OrthoCamera.SetRotation(45.0f);

		Ember::Renderer::BeginScene(OrthoCamera);
		Ember::Renderer::Submit(squareShader, squareVertexArray);
		Ember::Renderer::Submit(triangleShader, triangleVertexArray);

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






class GameLayer : public Ember::Layer
{
private:
	Grid grid;
	PlayerPos playerPos;
	std::array<std::array<std::shared_ptr<Ember::VertexArray>, 10>, 10> squareVertexArray;
	std::array<std::array<std::shared_ptr<Ember::VertexBuffer>, 10>, 10> squareVertexBuffer;
	std::array<std::array<std::shared_ptr<Ember::IndexBuffer>, 10>, 10> squareIndexBuffer;
	std::array<std::array<std::shared_ptr<Ember::Shader>, 10>, 10> squareShader;

	//---PLAYER-----------------------------------------
	std::shared_ptr<Ember::VertexArray> playerVertexArray;
	std::shared_ptr<Ember::VertexBuffer> playerVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> playerIndexBuffer;
	std::shared_ptr<Ember::Shader> playerShader;
	//--------------------------------------------------

	//---CAMERA-----------------------------------------
	Ember::OrthographicCamera OrthoCamera;
	//--------------------------------------------------
public:
	GameLayer()
		: Layer("Game"), OrthoCamera(-1.6f, 1.6f, -1.0f, 1.0f)
	{
		//---GRID----------------------------------------------------------------------------------------------------------------------

		grid.InitNewGrid(10, 10);

		playerPos.MaxXPos = 9;
		playerPos.MaxYPos = 9;

		for (uint16_t j = 0; j < 10; j++)
		{
			for (uint16_t i = 0; i < 10; i++)
			{
				squareVertexArray[j][i].reset(Ember::VertexArray::Create());

				squareVertexBuffer[j][i].reset(Ember::VertexBuffer::Create(grid.Vertices[j][i], sizeof(grid.Vertices[j][i])));

				squareVertexBuffer[j][i]->SetLayout({
					{ Ember::ShaderDataType::Vec3, "a_Position", false }
					});

				squareVertexArray[j][i]->AddVertexBuffer(squareVertexBuffer[j][i]);

				uint32_t squareIndices[6] = { 3, 2, 0, 0, 1, 3 };
				squareIndexBuffer[j][i].reset(Ember::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

				squareVertexArray[j][i]->SetIndexBuffer(squareIndexBuffer[j][i]);

				std::string vertexSrcSquare = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;

				out vec3 v_Position;
				out vec4 v_Colour;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

				squareShader[j][i].reset(new Ember::Shader(vertexSrcSquare, fragmentSrcSquare));
			}
		}

		//-----------------------------------------------------------------------------------------------------------------------------






		//---PLAYER-----------------------------------------

		playerVertexArray.reset(Ember::VertexArray::Create());

		playerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX], sizeof(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX])));

		playerVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false }
			});

		playerVertexArray->AddVertexBuffer(playerVertexBuffer);

		uint32_t squareIndices[6] = { 3, 2, 0, 0, 1, 3 };
		playerIndexBuffer.reset(Ember::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		playerVertexArray->SetIndexBuffer(playerIndexBuffer);

		std::string vertexSrcPlayer = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcPlayer = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			void main()
			{
				Colour = vec4(1.0, 0.0, 0.0, 1.0);
			}
		)";

		playerShader.reset(new Ember::Shader(vertexSrcPlayer, fragmentSrcPlayer));

		//--------------------------------------------------
	}

	void OnUpdate(Ember::DeltaTime DT) override
	{
		EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

		Ember::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ember::RenderCommand::Clear();

		Ember::Renderer::BeginScene(OrthoCamera);

		//Grid
		for (uint16_t j = 0; j < 10; j++)
		{
			for (uint16_t i = 0; i < 10; i++)
			{
				Ember::Renderer::Submit(squareShader[j][i], squareVertexArray[j][i]);
			}
		}
		//----

		Ember::Renderer::Submit(playerShader, playerVertexArray);

		Ember::Renderer::EndScene();
	}

	void OnEvent(Ember::Event& event) override
	{
		if (event.GetEventType() == Ember::EventType::KeyPressed)
		{
			Ember::KeyPressedEvent& e = (Ember::KeyPressedEvent&)event;
			EM_LOG_WARN("{0}", char(e.GetKeyCode()));

			if (e.GetKeyCode() == EM_KEY_D || e.GetKeyCode() == EM_KEY_RIGHT_ARROW)
			{
				if (playerPos.CurrentPosX != playerPos.MaxXPos)
				{
					playerPos.CurrentPosX += 1;

					playerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX], sizeof(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX])));

					playerVertexBuffer->SetLayout({
						{ Ember::ShaderDataType::Vec3, "a_Position", false }
						});

					playerVertexArray->AddVertexBuffer(playerVertexBuffer);
				}
			}
			if (e.GetKeyCode() == EM_KEY_A || e.GetKeyCode() == EM_KEY_LEFT_ARROW)
			{
				if (playerPos.CurrentPosX != 0)
				{
					playerPos.CurrentPosX -= 1;

					playerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX], sizeof(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX])));

					playerVertexBuffer->SetLayout({
						{ Ember::ShaderDataType::Vec3, "a_Position", false }
						});

					playerVertexArray->AddVertexBuffer(playerVertexBuffer);
				}
			}
			if (e.GetKeyCode() == EM_KEY_W || e.GetKeyCode() == EM_KEY_UP_ARROW)
			{
				if (playerPos.CurrentPosY != 0)
				{
					playerPos.CurrentPosY -= 1;

					playerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX], sizeof(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX])));

					playerVertexBuffer->SetLayout({
						{ Ember::ShaderDataType::Vec3, "a_Position", false }
						});

					playerVertexArray->AddVertexBuffer(playerVertexBuffer);
				}
			}
			if (e.GetKeyCode() == EM_KEY_S || e.GetKeyCode() == EM_KEY_DOWN_ARROW)
			{
				if (playerPos.CurrentPosY != playerPos.MaxYPos)
				{
					playerPos.CurrentPosY += 1;

					playerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX], sizeof(grid.Vertices[playerPos.CurrentPosY][playerPos.CurrentPosX])));

					playerVertexBuffer->SetLayout({
						{ Ember::ShaderDataType::Vec3, "a_Position", false }
						});

					playerVertexArray->AddVertexBuffer(playerVertexBuffer);
				}
			}
		}
	}
};






class GameApplication : public Ember::Application
{
public:
	GameApplication()
	{
		//PushLayer(new ExampleLayer);
		PushLayer(new GameLayer);
	}

	~GameApplication()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new GameApplication();
}