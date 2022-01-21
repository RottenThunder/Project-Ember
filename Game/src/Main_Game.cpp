#include "Main_Game.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

MainGame::MainGame()
	: Layer("MainGame"), Camera(-12.8f, 12.8f, -7.2f, 7.2f)
{

}

void MainGame::OnAttach()
{
	Player.Texture = Ember::Texture2D::Create("assets/textures/Link_Front.png");
	NPC.Texture = Ember::Texture2D::Create("assets/textures/Zelda_NPC_Front.png");

	Player.Position = { 9.0f, -4.0f, 0.1f };
	NPC.Position = { 3.0f, -7.0f, 0.0f };

	RoomMap = levelFileReader.Read("assets/levels/Room1.level");
	OutsideMap = levelFileReader.Read("assets/levels/Outside.level", 10, -40);
}

void MainGame::OnDetach()
{
	RoomMap.clear();
	OutsideMap.clear();
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
	ImGui::Text("CollisionCount: %i", CollisionCount);

	ImGui::End();
}

void MainGame::OnUpdate(Ember::DeltaTime DT)
{
	EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

	CollisionCount = 0;
	Player.TransformedPosition = Player.Position;

	Ember::RenderCommand::SetClearColour({ 0.25f, 0.25f, 0.25f, 1.0f });
	Ember::RenderCommand::Clear();

	Ember::Renderer2D::ResetStats();

	if (Ember::Input::IsKeyPressed(EM_KEY_D))
	{
		Player.TransformedPosition.x += playerSpeed * DT;
	}
	if (Ember::Input::IsKeyPressed(EM_KEY_A))
	{
		Player.TransformedPosition.x -= playerSpeed * DT;
	}
	if (Ember::Input::IsKeyPressed(EM_KEY_W))
	{
		Player.TransformedPosition.y += playerSpeed * DT;
	}
	if (Ember::Input::IsKeyPressed(EM_KEY_S))
	{
		Player.TransformedPosition.y -= playerSpeed * DT;
	}

	Ember::Renderer2D::BeginScene(Camera);

	for (Entity* x : RoomMap)
	{
		if ((-12.8f + Player.Position.x) < (x->Position.x + 0.5f) && (12.8f + Player.Position.x) > (x->Position.x - 0.5f) && (-7.2f + Player.Position.y) < (x->Position.y + 0.5f) && (7.2f + Player.Position.y) > (x->Position.y - 0.5f))
		{
			Ember::Renderer2D::DrawQuad(x->Position, { 1.0f, 1.0f }, x->Texture);
			if (x->IsCollidable)
			{
				CollisionCount += Player.CalculateAABBCollisions(Player.TransformedPosition, x->Position.x - 0.5f, x->Position.y - 0.5f);
			}
		}
	}
	for (Entity* x : OutsideMap)
	{
		if ((-12.8f + Player.Position.x) < (x->Position.x + 0.5f) && (12.8f + Player.Position.x) > (x->Position.x - 0.5f) && (-7.2f + Player.Position.y) < (x->Position.y + 0.5f) && (7.2f + Player.Position.y) > (x->Position.y - 0.5f))
		{
			Ember::Renderer2D::DrawQuad(x->Position, { 1.0f, 1.0f }, x->Texture);
			if (x->IsCollidable)
			{
				CollisionCount += Player.CalculateAABBCollisions(Player.TransformedPosition, x->Position.x - 0.5f, x->Position.y - 0.5f);
			}
		}
	}

	Ember::Renderer2D::DrawQuad(NPC.Position, { 1.0f, 2.0f }, NPC.Texture);
	CollisionCount += Player.CalculateAABBCollisions(Player.TransformedPosition, NPC.Position.x - 0.5f, NPC.Position.y - 1.0f);

	if (CollisionCount == 0)
	{
		Player.Position = Player.TransformedPosition;
	}

	Ember::Renderer2D::DrawQuad(Player.Position, { 1.0f, 2.0f }, Player.Texture);

	Camera.SetPosition(Player.Position);

	Ember::Renderer2D::EndScene();
}

void MainGame::OnEvent(Ember::Event& event)
{

}