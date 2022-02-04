#pragma once
#include <Ember.h>
#include <Ember/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"
#include "Player.h"
#include "Random.h"
#include "LevelFileReader.h"

class MainGame : public Ember::Layer
{
private:
	LevelFileReader levelFileReader;
	Random random;
	std::vector<Entity*> RoomMap;
	std::vector<Entity*> OutsideMap;
	Player player;
	Entity NPC;
	uint8_t CollisionCount = 0;
	Ember::OrthographicCamera Camera;

	bool InventoryOpen = false;

	uint16_t WindowWidth = 1280;
	uint16_t WindowHeight = 720;

	glm::vec2 PixelToWorldSpaceDivider;
public:
	MainGame();
	virtual ~MainGame() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnImGuiRender() override;
	void OnUpdate(Ember::DeltaTime DT) override;
	void OnEvent(Ember::Event& event) override;

	bool OnWindowResize(Ember::WindowResizeEvent& e);
	bool OnKeyReleased(Ember::KeyReleasedEvent& e);

	bool CalculateAABBCollisionsWithMouse(const glm::vec3& pos, float Qx, float Qy);
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