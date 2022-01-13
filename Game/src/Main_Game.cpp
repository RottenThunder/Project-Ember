#include "Main_Game.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

MainGame::MainGame()
	: Layer("MainGame"), OrthoCameraController(16.0f / 9.0f, 6.0f)
{

}

void MainGame::OnAttach()
{
	Player.Texture = Ember::Texture2D::Create("assets/textures/Link_Front.png");
	NPC.Texture = Ember::Texture2D::Create("assets/textures/Zelda_NPC_Front.png");
	Player.Position.x = 9.0f;
	Player.Position.y = -4.0f;
	Player.Position.z = 0.1f;
	NPC.Position.x = 3.0f;
	NPC.Position.y = -7.0f;

	Map = levelFileReader.Read("assets/levels/Room1.level");
}

void MainGame::OnDetach()
{

}

void MainGame::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Ember::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::NewLine();

	ImGui::Text("Position: %f, %f", Player.Position.x, Player.Position.y);
	ImGui::SliderFloat("Speed", &playerSpeed, 1.0f, 10.0f, "%.2f", 1.0f);
	ImGui::Text("CanMovePositiveX: %i", CanMovePositiveX);
	ImGui::Text("CanMoveNegativeX: %i", CanMoveNegativeX);
	ImGui::Text("CanMovePositiveY: %i", CanMovePositiveY);
	ImGui::Text("CanMoveNegativeY: %i", CanMoveNegativeY);

	ImGui::End();
}

void MainGame::OnUpdate(Ember::DeltaTime DT)
{
	//EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

	Ember::RenderCommand::SetClearColour({ 1.0f, 0.0f, 0.0f, 1.0f });
	Ember::RenderCommand::Clear();

	Ember::Renderer2D::ResetStats();

	if (CanMovePositiveX)
	{
		if (Ember::Input::IsKeyPressed(EM_KEY_D))
		{
			Player.Position.x += playerSpeed * DT;
		}
	}
	if (CanMoveNegativeX)
	{
		if (Ember::Input::IsKeyPressed(EM_KEY_A))
		{
			Player.Position.x -= playerSpeed * DT;
		}
	}
	if (CanMovePositiveY)
	{
		if (Ember::Input::IsKeyPressed(EM_KEY_W))
		{
			Player.Position.y += playerSpeed * DT;
		}
	}
	if (CanMoveNegativeY)
	{
		if (Ember::Input::IsKeyPressed(EM_KEY_S))
		{
			Player.Position.y -= playerSpeed * DT;
		}
	}

	Ember::Renderer2D::BeginScene(OrthoCameraController.GetCamera());

	for (auto x : Map)
	{
		Ember::Renderer2D::DrawQuad(x.Position, TileSize, x.Texture);
		if (x.IsCollidable)
		{
			Player.CalculateCollisions({ x.Position.x, x.Position.y + 0.5f, x.Position.z });
		}
	}

	Ember::Renderer2D::DrawQuad(NPC.Position, CharacterSize, NPC.Texture);
	Player.CalculateCollisions(NPC.Position);

	Player.HandleCollisions(CanMovePositiveX, CanMoveNegativeX, CanMovePositiveY, CanMoveNegativeY);
	Ember::Renderer2D::DrawQuad(Player.Position, CharacterSize, Player.Texture);

	OrthoCameraController.GetCamera().SetPosition(Player.Position);

	Ember::Renderer2D::EndScene();
}

void MainGame::OnEvent(Ember::Event& event)
{
	OrthoCameraController.OnEvent(event);
}