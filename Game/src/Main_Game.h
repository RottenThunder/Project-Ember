#pragma once
#include <Ember.h>
#include <Ember/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Random.h"
#include "LevelFileReader.h"

struct PreviewedCard
{
	uint8_t index;
	bool BeingPreviewed = false;
};

class MainGame : public Ember::Layer
{
private:
	bool DebugTabOpen = true; //For Debug

	LevelFileReader levelFileReader;
	std::vector<Entity*> RoomMap;
	std::vector<Entity*> OutsideMap;
	std::unordered_map<uint32_t, Enemy> Enemies;
	Player player;
	uint8_t CollisionCount = 0;
	Ember::OrthographicCamera Camera;

	Ember::Ref<Ember::Texture2D> ProjectileTexture;
	std::vector<Projectile> projectiles;

	bool CurrentCardsOpen = false;
	PreviewedCard previewedCard;
	bool MouseButton0Pressed = false;

	uint16_t WindowPosX = 0;
	uint16_t WindowPosY = 0;
	uint16_t WindowWidth = 1280;
	uint16_t WindowHeight = 720;

	glm::vec2 PixelToWorldSpaceDivider = { 0.0f, 0.0f };
public:
	MainGame();
	virtual ~MainGame() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnImGuiRender() override;
	void OnUpdate(Ember::DeltaTime DT) override;
	void OnEvent(Ember::Event& event) override;

	bool OnWindowMoved(Ember::WindowMovedEvent& e);
	bool OnWindowResize(Ember::WindowResizeEvent& e);
	bool OnKeyReleased(Ember::KeyReleasedEvent& e);
	bool OnMouseButtonPressed(Ember::MouseButtonPressedEvent& e);
	bool OnMouseButtonReleased(Ember::MouseButtonReleasedEvent& e);

	bool IsMouseOverCard(float x, float y);
	void DecodeCardEffect(size_t index);
};

class GameApplication : public Ember::Application
{
public:
	GameApplication()
	{
		//PushLayer(new Sandbox2D);
		PushLayer(new MainGame);
	}

	~GameApplication()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new GameApplication();
}