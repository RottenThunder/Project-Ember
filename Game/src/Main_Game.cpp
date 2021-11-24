#include <Ember.h>
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionHandler.h"
#include "Test(EntityPos).h"
#include "Grid.h"
#include "Random.h"

class ExampleLayer : public Ember::Layer
{
private:
	//---SQUARE-----------------------------------------
	Ember::Ref<Ember::VertexArray> squareVertexArray;
	Ember::Ref<Ember::VertexBuffer> squareVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> squareIndexBuffer;
	Ember::Ref<Ember::Shader> squareShader, squareTextureShader;
	Ember::Ref<Ember::Texture2D> squareTexture, squareTexture2;
	glm::vec3 squarePosition;
	glm::vec3 squareColour = { 0.9f, 0.1f, 0.4f };
	//--------------------------------------------------

	//---TRIANGLE---------------------------------------
	Ember::Ref<Ember::VertexArray> triangleVertexArray;
	Ember::Ref<Ember::VertexBuffer> triangleVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> triangleIndexBuffer;
	Ember::Ref<Ember::Shader> triangleShader;
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

		float_t SquareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, /*Bottom-Left*/ 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, /*Bottom-Right*/ 1.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, /*Top-Left*/ 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, /*Top-Right*/ 1.0f, 1.0f
		};

		squareVertexBuffer.reset(Ember::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

		squareVertexBuffer->SetLayout({
			{ Ember::ShaderDataType::Vec3, "a_Position", false },
			{ Ember::ShaderDataType::Vec2, "a_TexCoord", false }
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

			uniform vec3 u_Colour;

			void main()
			{
				Colour = vec4(u_Colour, 1.0);
			}
		)";

		squareShader.reset(Ember::Shader::Create(vertexSrcSquare, fragmentSrcSquare));


		std::string vertexSrcSquareTexture = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrcSquareTexture = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				Colour = texture(u_Texture, v_TexCoord);
			}
		)";

		squareTextureShader.reset(Ember::Shader::Create(vertexSrcSquareTexture, fragmentSrcSquareTexture));

		squareTexture = Ember::Texture2D::Create("assets/textures/Checkerboard.png");
		squareTexture2 = Ember::Texture2D::Create("assets/textures/TestCharacter_0001.png");

		std::dynamic_pointer_cast<Ember::OpenGLShader>(squareTextureShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(squareTextureShader)->UploadUniformInt("u_Texture", 0);

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
				Colour = vec4(0.0, 1.0, 0.0, 1.0);
			}
		)";

		triangleShader.reset(Ember::Shader::Create(vertexSrcTriangle, fragmentSrcTriangle));

		//--------------------------------------------------
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(squareColour));
		ImGui::End();
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
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::mat4 triangletransform = glm::translate(glm::mat4(1.0f), trianglePosition);

		std::dynamic_pointer_cast<Ember::OpenGLShader>(squareShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Colour", squareColour);

		Ember::Renderer::BeginScene(OrthoCamera);

		squareTexture->Bind();
		Ember::Renderer::Submit(squareTextureShader, squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		squareTexture2->Bind();
		Ember::Renderer::Submit(squareTextureShader, squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//Ember::Renderer::Submit(triangleShader, triangleVertexArray, triangletransform);

		/* Grid
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






class TestGameLayer : public Ember::Layer
{
private:
	Grid grid;
	Random random;
	PlayerPos playerPos;
	MonsterPos monsterPos;
	uint8_t gridX = 50;
	uint8_t gridY = 50;
	glm::vec2 Path = glm::vec2({ 0.0f, 0.0f });
	bool XMovementPossible = false;
	bool YMovementPossible = false;
	ImVec4 RedTextColour = ImVec4({ 1.0f, 0.0f, 0.0f, 1.0f });
	ImVec4 YellowTextColour = ImVec4({ 1.0f, 1.0f, 0.0f, 1.0f });
	bool AllowColourChange = false;
	bool SeePlayerPosition = false;
	bool SeeMonsterPosition = false;
	bool GameOver = false;

	//---BACKGROUND-------------------------------------
	Ember::Ref<Ember::VertexArray> backgroundVertexArray;
	Ember::Ref<Ember::VertexBuffer> backgroundVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> backgroundIndexBuffer;
	Ember::Ref<Ember::Shader> backgroundShader;
	glm::vec3 backgroundColour = { 0.0f, 1.0f, 0.0f };
	//--------------------------------------------------

	//---PLAYER-----------------------------------------
	Ember::Ref<Ember::VertexArray> playerVertexArray;
	Ember::Ref<Ember::VertexBuffer> playerVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> playerIndexBuffer;
	Ember::Ref<Ember::Shader> playerShader;
	float_t EventPlayerPositionX = 0.0f;
	float_t EventPlayerPositionY = 0.0f;
	glm::vec3 playerColour = { 1.0f, 0.0f, 0.0f };
	//--------------------------------------------------

	//---MONSTER----------------------------------------
	Ember::Ref<Ember::VertexArray> monsterVertexArray;
	Ember::Ref<Ember::VertexBuffer> monsterVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> monsterIndexBuffer;
	Ember::Ref<Ember::Shader> monsterShader;
	float_t EventMonsterPositionX = 0.0f;
	float_t EventMonsterPositionY = 0.0f;
	glm::vec3 monsterColour = { 0.0f, 0.0f, 1.0f };
	//--------------------------------------------------

	//---CAMERA-----------------------------------------
	Ember::OrthographicCamera OrthoCamera;
	glm::vec3 CameraPosition;
	float_t CameraSpeed = 1.0f;
	float_t CameraZoom = 0.0f;
	//--------------------------------------------------
public:
	TestGameLayer()
		: Layer("TestGame"), OrthoCamera(-3.2f, 3.2f, -1.8f, 1.8f), CameraPosition(0.0f)
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

			out vec4 v_Colour;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrcBackground = R"(
			#version 330 core

			layout(location = 0) out vec4 Colour;

			in vec4 v_Colour;

			uniform vec3 u_Colour;

			void main()
			{
				Colour = vec4(u_Colour, 1.0);
			}
		)";

		backgroundShader.reset(Ember::Shader::Create(vertexSrcBackground, fragmentSrcBackground));

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

			uniform vec3 u_Colour;

			void main()
			{
				Colour = vec4(u_Colour, 1.0);
			}
		)";

		playerShader.reset(Ember::Shader::Create(vertexSrcPlayer, fragmentSrcPlayer));

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

			uniform vec3 u_Colour;

			void main()
			{
				Colour = vec4(u_Colour, 1.0);
			}
		)";

		monsterShader.reset(Ember::Shader::Create(vertexSrcMonster, fragmentSrcMonster));

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

	void OnImGuiRender() override
	{
		ImGui::Begin("UI Test Window");
		ImGui::TextColored(YellowTextColour, "Controls");
		ImGui::NewLine();
		ImGui::Text("WASD - Move Player");
		ImGui::Text("Arrow Keys - Move Camera");
		ImGui::Text("Z - Zoom Camera In");
		ImGui::Text("X - Zoom Camera Out");
		ImGui::NewLine();
		if (!GameOver)
		{
			ImGui::TextColored(RedTextColour, "Try Changing The Colours!!!");
			ImGui::Checkbox("Allow Colour Change", &AllowColourChange);
			if (AllowColourChange)
			{
				ImGui::ColorEdit3("Background Colour", glm::value_ptr(backgroundColour));
				ImGui::ColorEdit3("Player Colour", glm::value_ptr(playerColour));
				ImGui::ColorEdit3("Monster Colour", glm::value_ptr(monsterColour));
			}
			ImGui::Checkbox("See Player Position", &SeePlayerPosition);
			if (SeePlayerPosition)
			{
				ImGui::Text("(%i, %i)", playerPos.CurrentPosX, playerPos.CurrentPosY);
			}
			ImGui::Checkbox("See Monster Position", &SeeMonsterPosition);
			if (SeeMonsterPosition)
			{
				ImGui::Text("(%i, %i)", monsterPos.CurrentPosX, monsterPos.CurrentPosY);
			}
			ImGui::Button("Reset Colours");
			if (ImGui::IsItemDeactivated())
			{
				backgroundColour = glm::vec3({ 0.0f, 1.0f, 0.0f });
				playerColour = glm::vec3({ 1.0f, 0.0f, 0.0f });
				monsterColour = glm::vec3({ 0.0f, 0.0f, 1.0f });
			}
		}
		else
		{
			ImGui::TextColored(RedTextColour, "Game Over!");
			ImGui::NewLine();
		}
		ImGui::Button("Reset Positions");
		if (ImGui::IsItemDeactivated())
		{
			EventPlayerPositionX = 0.0f;
			EventPlayerPositionY = 0.0f;
			EventMonsterPositionX = 0.0f;
			EventMonsterPositionY = 0.0f;
			playerPos.CurrentPosX = 0;
			playerPos.CurrentPosY = 0;
			monsterPos.CurrentPosX = monsterPos.MaxPosX;
			monsterPos.CurrentPosY = monsterPos.MaxPosY;
			GameOver = false;
		}
		ImGui::Text("%i x %i Grid", gridX, gridY);
		ImGui::End();
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

		std::dynamic_pointer_cast<Ember::OpenGLShader>(backgroundShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(backgroundShader)->UploadUniformFloat3("u_Colour", backgroundColour);
		Ember::Renderer::Submit(backgroundShader, backgroundVertexArray);

		glm::mat4 playertransform = glm::translate(glm::mat4(1.0f), glm::vec3(EventPlayerPositionX, EventPlayerPositionY, 0.0f));
		std::dynamic_pointer_cast<Ember::OpenGLShader>(playerShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(playerShader)->UploadUniformFloat3("u_Colour", playerColour);
		Ember::Renderer::Submit(playerShader, playerVertexArray, playertransform);

		glm::mat4 monstertransform = glm::translate(glm::mat4(1.0f), glm::vec3(EventMonsterPositionX, EventMonsterPositionY, 0.0f));
		std::dynamic_pointer_cast<Ember::OpenGLShader>(monsterShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(monsterShader)->UploadUniformFloat3("u_Colour", monsterColour);
		Ember::Renderer::Submit(monsterShader, monsterVertexArray, monstertransform);

		Ember::Renderer::EndScene();
	}

	void OnEvent(Ember::Event& event) override
	{
		if (event.GetEventType() == Ember::EventType::KeyPressed)
		{
			if (!GameOver)
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
				if ((playerPos.CurrentPosX == monsterPos.CurrentPosX) && (playerPos.CurrentPosY == monsterPos.CurrentPosY))
				{
					GameOver = true;
				}
			}
		}
	}
};



class GameLayer : public Ember::Layer
{
private:
	Player player;
	Enemy enemy;
	CollisionHandler collisionHandler;

	//---CAMERA-----------------------------------------
	Ember::OrthographicCamera OrthoCamera;
	//--------------------------------------------------
public:
	GameLayer()
		: Layer("Game"), OrthoCamera(-6.4f, 6.4f, -3.6f, 3.6f)
	{
		player.Init();
		enemy.Init();
		enemy.EnemyPosition = { -4.0f, 0.0f, 0.0f };
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Player Colliders");
		ImGui::Text("Top Left: %i", player.TopLeftColliding);
		ImGui::Text("Top Right: %i", player.TopRightColliding);
		ImGui::Text("Bottom Left: %i", player.BottomLeftColliding);
		ImGui::Text("Bottom Right: %i", player.BottomRightColliding);
		ImGui::NewLine();
		ImGui::Text("CanMove+X: %i", collisionHandler.CanMovePositiveX);
		ImGui::Text("CanMove-X: %i", collisionHandler.CanMoveNegativeX);
		ImGui::Text("CanMove+Y: %i", collisionHandler.CanMovePositiveY);
		ImGui::Text("CanMove-Y: %i", collisionHandler.CanMoveNegativeY);
		ImGui::End();
	}

	void OnUpdate(Ember::DeltaTime DT) override
	{
		//EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());
		player.SetColliderValues();
		enemy.SetColliderValues();

		Ember::RenderCommand::SetClearColour({ 0.0f, 1.0f, 0.0f, 1.0f });
		Ember::RenderCommand::Clear();

		collisionHandler.HandleCollisionsForPlayer(player, enemy.MinColliderPosition, enemy.MaxColliderPosition);
		collisionHandler.BlockMovementForPlayer(player, enemy.MinColliderPosition, enemy.MaxColliderPosition);

		if (collisionHandler.CanMovePositiveX)
		{
			if (Ember::Input::IsKeyPressed(EM_KEY_D))
			{
				player.PlayerPosition.x += player.PlayerSpeed * DT;
			}
		}
		if (collisionHandler.CanMoveNegativeX)
		{
			if (Ember::Input::IsKeyPressed(EM_KEY_A))
			{
				player.PlayerPosition.x -= player.PlayerSpeed * DT;
			}
		}
		if (collisionHandler.CanMovePositiveY)
		{
			if (Ember::Input::IsKeyPressed(EM_KEY_W))
			{
				player.PlayerPosition.y += player.PlayerSpeed * DT;
			}
		}
		if (collisionHandler.CanMoveNegativeY)
		{
			if (Ember::Input::IsKeyPressed(EM_KEY_S))
			{
				player.PlayerPosition.y -= player.PlayerSpeed * DT;
			}
		}

		player.UpdateTransform();
		enemy.UpdateTransform();

		Ember::Renderer::BeginScene(OrthoCamera);

		enemy.EnemyTexture->Bind();
		Ember::Renderer::Submit(enemy.EnemyTextureShader, enemy.EnemyVertexArray, enemy.EnemyTransform);

		player.PlayerTexture->Bind();
		Ember::Renderer::Submit(player.PlayerTextureShader, player.PlayerVertexArray, player.PlayerTransform);

		Ember::Renderer::EndScene();
	}

	void OnEvent(Ember::Event& event) override
	{

	}
};








class GameApplication : public Ember::Application
{
public:
	GameApplication()
	{
		//PushLayer(new ExampleLayer);
		//PushLayer(new TestGameLayer);
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