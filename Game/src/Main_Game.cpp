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
	ProjectileTexture = Ember::Texture2D::Create("assets/textures/Projectile.png");
	NPC.Texture = Ember::Texture2D::Create("assets/textures/Zelda_NPC_Front.png");
	player.AddToCurrentCards(0x0001);
	player.AddToCurrentCards(0x0002);
	player.AddToCurrentCards(0x0003);

	player.Position = { 9.0f, -4.0f, 0.1f };
	NPC.Position = { 10.0f, -10.0f, 0.0f };

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
	if (DebugTabOpen)
	{
		ImGui::Begin("Debug");

		ImGui::Text("---Press ENTER To Close Debug Tab---");

		ImGui::NewLine();

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
		ImGui::SliderFloat("Attack Power", &player.AttackPower, 1.0f, 10.0f, "%.2f", 1.0f);
		ImGui::Text("ProjectileCount: %i", projectiles.size());
		ImGui::Text("CollisionCount: %i", CollisionCount);
		ImGui::Text("Amount of Cards Hold: %i", player.CurrentCards.size());

		ImGui::NewLine();

		ImGui::Text("Controls:");
		ImGui::Text("W - Move Up");
		ImGui::Text("A - Move Left");
		ImGui::Text("S - Move Down");
		ImGui::Text("D - Move Right");
		ImGui::Text("SPACE - Fire Projectile");
		ImGui::Text("C - Current Cards");
		ImGui::Text("1 - To use Card 1");
		ImGui::Text("2 - To use Card 2");
		ImGui::Text("3 - To use Card 3");
		ImGui::Text("4 - To use Card 4");
		ImGui::Text("5 - To use Card 5");

		ImGui::End();
	}
}

void MainGame::OnUpdate(Ember::DeltaTime DT)
{
	//EM_LOG_INFO("Delta Time: {0}s, {1}ms", DT.GetSeconds(), DT.GetMilliseconds());

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

	if (previewedCard.BeingPreviewed)
	{
		Ember::Renderer2D::DrawQuad({ player.Position.x, player.Position.y, 0.1f }, { 5.0f, 7.5f }, player.CurrentCards[previewedCard.index]);
		if (MouseButton0Pressed)
		{
			previewedCard.BeingPreviewed = false;
		}
	}

	if (CurrentCardsOpen)
	{
		for (uint8_t i = 0; i < player.CurrentCards.size(); i++)
		{
			Ember::Renderer2D::DrawQuad({ player.Position.x + player.CardPos[i], player.Position.y - 5.5f, 0.3f }, { 2.0f, 3.0f }, player.CurrentCards[i]);
			//EM_LOG_DEBUG("Name = {0}, Tier = {1}, Effect = {2}", player.CurrentCardsInfo.at(i).GetName(), player.CurrentCardsInfo.at(i).GetTier(), player.CurrentCardsInfo.at(i).GetEffect());
			if (IsMouseOverCard(player.Position.x + player.CardPos[i], player.Position.y - 5.5f))
			{
				if (!previewedCard.BeingPreviewed && MouseButton0Pressed)
				{
					previewedCard.BeingPreviewed = true;
					previewedCard.index = i;
				}
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

	for (uint8_t i = 0; i < projectiles.size(); i++)
	{
		Ember::Renderer2D::DrawRotatedQuad(projectiles[i].Position, { 1.0f, 1.0f }, projectiles[i].Rotation, ProjectileTexture);
		if (NPC.CalculateAABBCollisions(NPC.Position, projectiles[i].Position.x - 0.5f, projectiles[i].Position.y - 0.5f))
		{
			EM_LOG_WARN("Projetile did {0} damage", player.AttackPower);
			projectiles[i].CanDestroy = true;
		}
		projectiles[i].Travel(DT);
	}
	for (const auto& proj : projectiles)
	{
		if (proj.CanDestroy)
		{
			projectiles.erase(projectiles.begin());
		}
	}

	Camera.SetPosition(player.Position);

	Ember::Renderer2D::EndScene();
}

void MainGame::OnEvent(Ember::Event& event)
{
	Ember::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Ember::WindowMovedEvent>(EM_BIND_EVENT_FUNC(MainGame::OnWindowMoved));
	dispatcher.Dispatch<Ember::WindowResizeEvent>(EM_BIND_EVENT_FUNC(MainGame::OnWindowResize));
	dispatcher.Dispatch<Ember::KeyReleasedEvent>(EM_BIND_EVENT_FUNC(MainGame::OnKeyReleased));
	dispatcher.Dispatch<Ember::MouseButtonPressedEvent>(EM_BIND_EVENT_FUNC(MainGame::OnMouseButtonPressed));
	dispatcher.Dispatch<Ember::MouseButtonReleasedEvent>(EM_BIND_EVENT_FUNC(MainGame::OnMouseButtonReleased));
}

bool MainGame::OnWindowMoved(Ember::WindowMovedEvent& e)
{
	WindowPosX = e.GetX();
	WindowPosY = e.GetY();

	return false;
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
	if (e.GetKeyCode() == EM_KEY_ENTER)
	{
		DebugTabOpen ^= 0x01;
	}

	if (e.GetKeyCode() == EM_KEY_C)
	{
		CurrentCardsOpen ^= 0x01;
	}

	if (e.GetKeyCode() == EM_KEY_SPACE)
	{
		projectiles.emplace_back(glm::vec3(player.Position.x, player.Position.y, 0.2f), (uint8_t)player.Face, 5.0f, 10.0f);
	}

	if (e.GetKeyCode() == EM_KEY_1)
	{
		if (player.CurrentCards.size() > 0)
		{
			DecodeCardEffect(0);
			player.RemoveFromCurrentCards(0);
		}
	}
	if (e.GetKeyCode() == EM_KEY_2)
	{
		if (player.CurrentCards.size() > 1)
		{
			DecodeCardEffect(1);
			player.RemoveFromCurrentCards(1);
		}
	}
	if (e.GetKeyCode() == EM_KEY_3)
	{
		if (player.CurrentCards.size() > 2)
		{
			DecodeCardEffect(2);
			player.RemoveFromCurrentCards(2);
		}
	}
	if (e.GetKeyCode() == EM_KEY_4)
	{
		if (player.CurrentCards.size() > 3)
		{
			DecodeCardEffect(3);
			player.RemoveFromCurrentCards(3);
		}
	}
	if (e.GetKeyCode() == EM_KEY_5)
	{
		if (player.CurrentCards.size() > 4)
		{
			DecodeCardEffect(4);
			player.RemoveFromCurrentCards(4);
		}
	}

	return false;
}

bool MainGame::OnMouseButtonPressed(Ember::MouseButtonPressedEvent& e)
{
	if (e.GetMouseButton() == 0)
	{
		MouseButton0Pressed = true;
	}

	return false;
}

bool MainGame::OnMouseButtonReleased(Ember::MouseButtonReleasedEvent& e)
{
	if (e.GetMouseButton() == 0)
	{
		MouseButton0Pressed = false;
	}

	return false;
}

bool MainGame::IsMouseOverCard(float x, float y)
{
	float_t MouseX = (Ember::Input::GetMouseX() / PixelToWorldSpaceDivider.x) - 12.8f + player.Position.x;
	float_t MouseY = 14.4f - (Ember::Input::GetMouseY() / PixelToWorldSpaceDivider.y) - 7.2f + player.Position.y;

	if (MouseX < (x + 1.0f) && MouseX > (x - 1.0f) && MouseY < (y + 1.5f) && MouseY > (y - 1.5f))
	{
		return true;
	}

	return false;
}

void MainGame::DecodeCardEffect(size_t index)
{
	switch (player.CurrentCardsInfo[index].GetEffect())
	{
	case 0x00:
		break;
	case 0x01:
		player.Speed += (player.Speed * 0.5f);
		break;
	case 0x02:
		player.Speed += (player.Speed * 0.65f);
		break;
	case 0x03:
		player.Speed += (player.Speed * 0.8f);
		break;
	}
}