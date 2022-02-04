#include "Main_Game.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

MainGame::MainGame()
	: Layer("MainGame"), Camera(-12.8f, 12.8f, -7.2f, 7.2f)
{

}

void MainGame::OnAttach()
{
	PixelToWorldSpaceDivider.x = WindowWidth / 25.6f;
	PixelToWorldSpaceDivider.y = WindowHeight / 14.4f;

	player.Texture = Ember::Texture2D::Create("assets/textures/Pokemon_Player_Front.png");
	player.Face = PlayerFace::Down;
	player.AddToInventory(0x0003, 0x01);
	player.AddToInventory(0x0001, 0x04);
	player.AddToInventory(0x0002, 0x37);
	NPC.Texture = Ember::Texture2D::Create("assets/textures/Zelda_NPC_Front.png");

	player.Position = { 9.0f, -4.0f, 0.1f };
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
	ImGui::Text("Draw Calls: %i", stats.DrawCalls);
	ImGui::Text("Quads: %i", stats.QuadCount);
	ImGui::Text("Vertices: %i", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %i", stats.GetTotalIndexCount());

	ImGui::NewLine();

	ImGui::Text("Player Stats:");
	ImGui::Text("Position: %f, %f", player.Position.x, player.Position.y);
	ImGui::SliderFloat("Speed", &player.Speed, 1.0f, 10.0f, "%.2f", 1.0f);
	ImGui::Text("CollisionCount: %i", CollisionCount);

	ImGui::NewLine();

	ImGui::Text("Controls:");
	ImGui::Text("W - Move Up");
	ImGui::Text("A - Move Left");
	ImGui::Text("S - Move Down");
	ImGui::Text("D - Move Right");
	ImGui::Text("I - Inventory");

	ImGui::End();
}

void MainGame::OnUpdate(Ember::DeltaTime DT)
{
	EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

	CollisionCount = 0;
	player.TransformedPosition = player.Position;
	PlayerFace newFace = player.Face;

	Ember::RenderCommand::SetClearColour({ 0.25f, 0.25f, 0.25f, 1.0f });
	Ember::RenderCommand::Clear();

	Ember::Renderer2D::ResetStats();

	if (Ember::Input::IsKeyPressed(EM_KEY_D))
	{
		player.TransformedPosition.x += player.Speed * DT;
		newFace = PlayerFace::Right;
	}
	if (Ember::Input::IsKeyPressed(EM_KEY_A))
	{
		player.TransformedPosition.x -= player.Speed * DT;
		newFace = PlayerFace::Left;
	}
	if (Ember::Input::IsKeyPressed(EM_KEY_W))
	{
		player.TransformedPosition.y += player.Speed * DT;
		newFace = PlayerFace::Up;
	}
	if (Ember::Input::IsKeyPressed(EM_KEY_S))
	{
		player.TransformedPosition.y -= player.Speed * DT;
		newFace = PlayerFace::Down;
	}

	Ember::Renderer2D::BeginScene(Camera);

	if (InventoryOpen)
	{
		Ember::Renderer2D::DrawQuad({ player.Position.x, player.Position.y, 0.2f }, { 15.0f, 9.0f }, { 0.0f, 0.0f, 0.1f, 1.0f });
		for (uint8_t i = 0; i < player.Inventory.size(); i++)
		{
			glm::vec3 inventorySlotPos = { player.Position.x + player.InventorySlotPositions.at(i).x, player.Position.y + player.InventorySlotPositions.at(i).y, 0.3f };
			Ember::Renderer2D::DrawQuad(inventorySlotPos, { 1.0f, 1.0f }, player.Inventory.at(i));
			glm::vec3 mousePos = { player.Position.x + ((Ember::Input::GetMouseX() / PixelToWorldSpaceDivider.x) - 12.8f), player.Position.y + (((Ember::Input::GetMouseY() / PixelToWorldSpaceDivider.y) - 7.2f) * -1.0f), 0.3f };
			if (CalculateAABBCollisionsWithMouse(mousePos, inventorySlotPos.x - 0.5f, inventorySlotPos.y - 0.5f))
			{
				Ember::Renderer2D::DrawQuad({ mousePos.x + 2.0f, mousePos.y, 0.4f }, { 3.0f, 6.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
			}
		}
	}

	for (Entity* x : RoomMap)
	{
		if ((-12.8f + player.Position.x) < (x->Position.x + 0.5f) && (12.8f + player.Position.x) > (x->Position.x - 0.5f) && (-7.2f + player.Position.y) < (x->Position.y + 0.5f) && (7.2f + player.Position.y) > (x->Position.y - 0.5f))
		{
			Ember::Renderer2D::DrawQuad(x->Position, { 1.0f, 1.0f }, x->Texture);
			if (x->IsCollidable)
			{
				CollisionCount += player.CalculateAABBCollisions(player.TransformedPosition, x->Position.x - 0.5f, x->Position.y - 0.5f);
			}
		}
	}
	for (Entity* x : OutsideMap)
	{
		if ((-12.8f + player.Position.x) < (x->Position.x + 0.5f) && (12.8f + player.Position.x) > (x->Position.x - 0.5f) && (-7.2f + player.Position.y) < (x->Position.y + 0.5f) && (7.2f + player.Position.y) > (x->Position.y - 0.5f))
		{
			Ember::Renderer2D::DrawQuad(x->Position, { 1.0f, 1.0f }, x->Texture);
			if (x->IsCollidable)
			{
				CollisionCount += player.CalculateAABBCollisions(player.TransformedPosition, x->Position.x - 0.5f, x->Position.y - 0.5f);
			}
		}
	}

	Ember::Renderer2D::DrawQuad(NPC.Position, { 1.0f, 2.0f }, NPC.Texture);
	CollisionCount += player.CalculateAABBCollisions(player.TransformedPosition, NPC.Position.x - 0.5f, NPC.Position.y - 1.0f);

	if (CollisionCount == 0)
	{
		player.Position = player.TransformedPosition;
	}
	if (newFace != player.Face)
	{
		if (newFace == PlayerFace::Down)
		{
			player.Texture = Ember::Texture2D::Create("assets/textures/Pokemon_Player_Front.png");
		}
		if (newFace == PlayerFace::Left)
		{
			player.Texture = Ember::Texture2D::Create("assets/textures/Pokemon_Player_Left.png");
		}
		if (newFace == PlayerFace::Up)
		{
			player.Texture = Ember::Texture2D::Create("assets/textures/Pokemon_Player_Back.png");
		}
		if (newFace == PlayerFace::Right)
		{
			player.Texture = Ember::Texture2D::Create("assets/textures/Pokemon_Player_Right.png");
		}

		player.Face = newFace;
	}

	Ember::Renderer2D::DrawQuad(player.Position, { 1.0f, 2.0f }, player.Texture);

	Camera.SetPosition(player.Position);

	Ember::Renderer2D::EndScene();
}

void MainGame::OnEvent(Ember::Event& event)
{
	Ember::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Ember::WindowResizeEvent>(EM_BIND_EVENT_FUNC(MainGame::OnWindowResize));
	dispatcher.Dispatch<Ember::KeyReleasedEvent>(EM_BIND_EVENT_FUNC(MainGame::OnKeyReleased));
}

bool MainGame::OnWindowResize(Ember::WindowResizeEvent& e)
{
	WindowWidth = e.GetWidth();
	WindowHeight = e.GetHeight();

	PixelToWorldSpaceDivider.x = WindowWidth / 25.6f;
	PixelToWorldSpaceDivider.y = WindowHeight / 14.4f;

	return false;
}

bool MainGame::OnKeyReleased(Ember::KeyReleasedEvent& e)
{
	if (e.GetKeyCode() == EM_KEY_I)
	{
		if (InventoryOpen)
		{
			InventoryOpen = false;
		}
		else
		{
			InventoryOpen = true;
		}
	}

	return false;
}

bool MainGame::CalculateAABBCollisionsWithMouse(const glm::vec3& pos, float Qx, float Qy)
{
	if (pos.x < (Qx + 1.0f) && pos.x > Qx && pos.y < (Qy + 1.0f) && pos.y > Qy)
	{
		return true;
	}

	return false;
}