#include <Ember.h>
#include "glm/gtc/matrix_transform.hpp"
#include "EntityPos.h"
#include "Grid.h"
#include "Random.h"

class ExampleLayer : public Ember::Layer
{
private:
	//---SQUARE-----------------------------------------
	std::shared_ptr<Ember::VertexArray> squareVertexArray;
	std::shared_ptr<Ember::VertexBuffer> squareVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> squareIndexBuffer;
	std::shared_ptr<Ember::Shader> squareShader;
	glm::vec3 squarePosition;
	//--------------------------------------------------

	//---TRIANGLE---------------------------------------
	std::shared_ptr<Ember::VertexArray> triangleVertexArray;
	std::shared_ptr<Ember::VertexBuffer> triangleVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> triangleIndexBuffer;
	std::shared_ptr<Ember::Shader> triangleShader;
	glm::vec3 trianglePosition;
	//--------------------------------------------------

	//---CAMERA-----------------------------------------
	Ember::OrthographicCamera OrthoCamera;
	//--------------------------------------------------
public:
	ExampleLayer()
		: Layer("Example"), OrthoCamera(-1.6f, 1.6f, -0.9f, 0.9f), squarePosition(0.0f), trianglePosition(0.0f)
	{

		//---SQUARE-----------------------------------------

		squareVertexArray.reset(Ember::VertexArray::Create());

		float_t SquareVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f, //Bottom-Left
			0.5f, -0.5f, 0.0f, //Bottom-Right
			-0.5f, 0.5f, 0.0f, //Top-Left
			0.5f, 0.5f, 0.0f //Top-Right
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
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		//OrthoCamera.SetPosition({ 0.5f, 0.5f, 0.0f });
		//OrthoCamera.SetRotation(45.0f);

		if (Ember::Input::IsKeyPressed(EM_KEY_I))
		{
			squarePosition.y += 1.0f * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_K))
		{
			squarePosition.y -= 1.0f * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_L))
		{
			squarePosition.x += 1.0f * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_J))
		{
			squarePosition.x -= 1.0f * DT;
		}

		if (Ember::Input::IsKeyPressed(EM_KEY_W))
		{
			trianglePosition.y += 1.0f * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_S))
		{
			trianglePosition.y -= 1.0f * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_D))
		{
			trianglePosition.x += 1.0f * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_A))
		{
			trianglePosition.x -= 1.0f * DT;
		}

		glm::mat4 squaretransform = glm::translate(glm::mat4(1.0f), squarePosition);
		//static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::mat4 triangletransform = glm::translate(glm::mat4(1.0f), trianglePosition);

		Ember::Renderer::BeginScene(OrthoCamera);
		Ember::Renderer::Submit(squareShader, squareVertexArray, squaretransform);
		Ember::Renderer::Submit(triangleShader, triangleVertexArray, triangletransform);

		/*
		for (uint8_t j = 0; j < 5; j++)
		{
			for (uint8_t i = 0; i < 5; i++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 squaretransform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Ember::Renderer::Submit(squareShader, squareVertexArray, squaretransform);
			}
		}
		*/

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
	Random random;
	PlayerPos playerPos;
	MonsterPos monsterPos;
	uint8_t gridX = 40;
	uint8_t gridY = 40;
	glm::vec2 Path = glm::vec2({ 0.0f, 0.0f });
	bool XMovementPossible = false;
	bool YMovementPossible = false;

	//---BACKGROUND-------------------------------------
	std::shared_ptr<Ember::VertexArray> backgroundVertexArray;
	std::shared_ptr<Ember::VertexBuffer> backgroundVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> backgroundIndexBuffer;
	std::shared_ptr<Ember::Shader> backgroundShader;
	//--------------------------------------------------

	//---PLAYER-----------------------------------------
	std::shared_ptr<Ember::VertexArray> playerVertexArray;
	std::shared_ptr<Ember::VertexBuffer> playerVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> playerIndexBuffer;
	std::shared_ptr<Ember::Shader> playerShader;
	float_t EventPlayerPositionX = 0.0f;
	float_t EventPlayerPositionY = 0.0f;
	//--------------------------------------------------

	//---MONSTER----------------------------------------
	std::shared_ptr<Ember::VertexArray> monsterVertexArray;
	std::shared_ptr<Ember::VertexBuffer> monsterVertexBuffer;
	std::shared_ptr<Ember::IndexBuffer> monsterIndexBuffer;
	std::shared_ptr<Ember::Shader> monsterShader;
	float_t EventMonsterPositionX = 0.0f;
	float_t EventMonsterPositionY = 0.0f;
	//--------------------------------------------------

	//---CAMERA-----------------------------------------
	Ember::OrthographicCamera OrthoCamera;
	glm::vec3 CameraPosition;
	float_t CameraSpeed = 1.0f;
	float_t CameraZoom = 0.0f;
	//--------------------------------------------------
public:
	GameLayer()
		: Layer("Game"), OrthoCamera(-3.2f, 3.2f, -1.8f, 1.8f), CameraPosition(0.0f)
	{
		grid.InitNewGrid(gridX, gridY);

		//---BACKGROUND-----------------------------------------


		backgroundVertexArray.reset(Ember::VertexArray::Create());

		float_t BackgroundVertices[3 * 4] =
		{
			-1.0f, -1.0f, 0.0f, //Bottom-Left
			1.0f, -1.0f, 0.0f, //Bottom-Right
			-1.0f, 1.0f, 0.0f, //Top-Left
			1.0f, 1.0f, 0.0f //Top-Right
		};

		backgroundVertexBuffer.reset(Ember::VertexBuffer::Create(BackgroundVertices, sizeof(BackgroundVertices)));

		backgroundVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false }
			});

		backgroundVertexArray->AddVertexBuffer(backgroundVertexBuffer);

		uint32_t backgroundIndices[6] = { 3, 2, 0, 0, 1, 3 };
		backgroundIndexBuffer.reset(Ember::IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));

		backgroundVertexArray->SetIndexBuffer(backgroundIndexBuffer);

		std::string vertexSrcBackground = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrcBackground = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec3 v_Position;
			in vec4 v_Colour;

			void main()
			{
				Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		backgroundShader.reset(new Ember::Shader(vertexSrcBackground, fragmentSrcBackground));

		//--------------------------------------------------






		//---PLAYER-----------------------------------------

		playerPos.MaxPosX = gridX - 1;
		playerPos.MaxPosY = gridY - 1;

		playerVertexArray.reset(Ember::VertexArray::Create());

		playerVertexBuffer.reset(Ember::VertexBuffer::Create(grid.TopLeftVertices, sizeof(grid.TopLeftVertices)));

		playerVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false }
			});

		playerVertexArray->AddVertexBuffer(playerVertexBuffer);

		uint32_t playerIndices[6] = { 3, 2, 0, 0, 1, 3 };
		playerIndexBuffer.reset(Ember::IndexBuffer::Create(playerIndices, sizeof(playerIndices) / sizeof(uint32_t)));

		playerVertexArray->SetIndexBuffer(playerIndexBuffer);

		std::string vertexSrcPlayer = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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





		//---MONSTER----------------------------------------

		monsterPos.CurrentPosX = gridX - 1;
		monsterPos.CurrentPosY = gridY - 1;
		monsterPos.MaxPosX = gridX - 1;
		monsterPos.MaxPosY = gridY - 1;

		monsterVertexArray.reset(Ember::VertexArray::Create());

		monsterVertexBuffer.reset(Ember::VertexBuffer::Create(grid.BottomRightVertices, sizeof(grid.BottomRightVertices)));

		monsterVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false }
			});

		monsterVertexArray->AddVertexBuffer(monsterVertexBuffer);

		uint32_t monsterIndices[6] = { 3, 2, 0, 0, 1, 3 };
		monsterIndexBuffer.reset(Ember::IndexBuffer::Create(monsterIndices, sizeof(monsterIndices) / sizeof(uint32_t)));

		monsterVertexArray->SetIndexBuffer(monsterIndexBuffer);

		std::string vertexSrcMonster = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcMonster = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			void main()
			{
				Colour = vec4(0.0, 0.0, 1.0, 1.0);
			}
		)";

		monsterShader.reset(new Ember::Shader(vertexSrcMonster, fragmentSrcMonster));

		//--------------------------------------------------

	}

	void PathFind()
	{
		Path.x = monsterPos.CurrentPosX - playerPos.CurrentPosX;
		Path.y = monsterPos.CurrentPosY - playerPos.CurrentPosY;
		if (Path.x > 0 || Path.x < 0)
		{
			XMovementPossible = true;
		}
		if (Path.y > 0 || Path.y < 0)
		{
			YMovementPossible = true;
		}
		if (XMovementPossible == true && YMovementPossible == false)
		{
			MonsterMoveX();
		}
		if (YMovementPossible == true && XMovementPossible == false)
		{
			MonsterMoveY();
		}
		if (XMovementPossible == true && YMovementPossible == true)
		{
			uint8_t randomDecision = random.GenerateBinaryValue();
			if (randomDecision == 0)
			{
				MonsterMoveX();
			}
			if (randomDecision == 1)
			{
				MonsterMoveY();
			}
		}
		XMovementPossible = false;
		YMovementPossible = false;
	}

	void MonsterMoveX()
	{
		if (Path.x > 0) // Move Left
		{
			EventMonsterPositionX -= grid.IntervalX;
			monsterPos.CurrentPosX -= 1;
		}

		if (Path.x < 0) // Move Right
		{
			EventMonsterPositionX += grid.IntervalX;
			monsterPos.CurrentPosX += 1;
		}
	}

	void MonsterMoveY()
	{
		if (Path.y > 0) // Move Up
		{
			EventMonsterPositionY += grid.IntervalY;
			monsterPos.CurrentPosY -= 1;
		}

		if (Path.y < 0) // Move Down
		{
			EventMonsterPositionY -= grid.IntervalY;
			monsterPos.CurrentPosY += 1;
		}
	}

	void OnUpdate(Ember::DeltaTime DT) override
	{
		//EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

		if (Ember::Input::IsKeyPressed(EM_KEY_LEFT_ARROW))
		{
			CameraPosition.x -= CameraSpeed * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_RIGHT_ARROW))
		{
			CameraPosition.x += CameraSpeed * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_UP_ARROW))
		{
			CameraPosition.y += CameraSpeed * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_DOWN_ARROW))
		{
			CameraPosition.y -= CameraSpeed * DT;
		}

		if (Ember::Input::IsKeyPressed(EM_KEY_Z))
		{
			CameraZoom += CameraSpeed * DT;
		}
		if (Ember::Input::IsKeyPressed(EM_KEY_X))
		{
			CameraZoom -= CameraSpeed * DT;
		}

		Ember::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ember::RenderCommand::Clear();

		OrthoCamera = Ember::OrthographicCamera(-3.2f + CameraZoom, 3.2f - CameraZoom, -1.8f + ((9.0f / 16.0f) * CameraZoom), 1.8f - ((9.0f / 16.0f) * CameraZoom));
		OrthoCamera.SetPosition(CameraPosition);

		Ember::Renderer::BeginScene(OrthoCamera);

		Ember::Renderer::Submit(backgroundShader, backgroundVertexArray);

		glm::mat4 playertransform = glm::translate(glm::mat4(1.0f), glm::vec3(EventPlayerPositionX, EventPlayerPositionY, 0.0f));
		Ember::Renderer::Submit(playerShader, playerVertexArray, playertransform);

		glm::mat4 monstertransform = glm::translate(glm::mat4(1.0f), glm::vec3(EventMonsterPositionX, EventMonsterPositionY, 0.0f));
		Ember::Renderer::Submit(monsterShader, monsterVertexArray, monstertransform);

		Ember::Renderer::EndScene();
	}

	void OnEvent(Ember::Event& event) override
	{
		if (event.GetEventType() == Ember::EventType::KeyPressed)
		{
			Ember::KeyPressedEvent& e = (Ember::KeyPressedEvent&)event;
			if (e.GetKeyCode() == EM_KEY_D)
			{
				if (playerPos.CurrentPosX != playerPos.MaxPosX)
				{
					EventPlayerPositionX += grid.IntervalX;
					playerPos.CurrentPosX += 1;
					PathFind();
				}
			}
			if (e.GetKeyCode() == EM_KEY_A)
			{
				if (playerPos.CurrentPosX != 0)
				{
					EventPlayerPositionX -= grid.IntervalX;
					playerPos.CurrentPosX -= 1;
					PathFind();
				}
			}
			if (e.GetKeyCode() == EM_KEY_W)
			{
				if (playerPos.CurrentPosY != 0)
				{
					EventPlayerPositionY += grid.IntervalY;
					playerPos.CurrentPosY -= 1;
					PathFind();
				}
			}
			if (e.GetKeyCode() == EM_KEY_S)
			{
				if (playerPos.CurrentPosY != playerPos.MaxPosY)
				{
					EventPlayerPositionY -= grid.IntervalY;
					playerPos.CurrentPosY += 1;
					PathFind();
				}
			}
			EM_LOG_DEBUG("Player: X: {0}, Y: {1}", playerPos.CurrentPosX, playerPos.CurrentPosY);
			EM_LOG_DEBUG("Monster: X: {0}, Y: {1}", monsterPos.CurrentPosX, monsterPos.CurrentPosY);
			if ((playerPos.CurrentPosX == monsterPos.CurrentPosX) && (playerPos.CurrentPosY == monsterPos.CurrentPosY))
			{
				EM_LOG_ERROR("GAME OVER!");
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
		PushOverlay(new Ember::ImGuiLayer);
	}

	~GameApplication()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new GameApplication();
}