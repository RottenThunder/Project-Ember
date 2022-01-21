#pragma once
#include <Ember.h>
#include <Ember/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"
#include "Entity.h"
#include "Random.h"
#include "LevelFileReader.h"

class MainGame : public Ember::Layer
{
private:
	LevelFileReader levelFileReader;
	std::vector<Entity*> RoomMap;
	std::vector<Entity*> OutsideMap;
	Entity Player;
	uint8_t CollisionCount = 0;
	float_t playerSpeed = 2.0f;
	Entity NPC;
	Ember::OrthographicCamera Camera;
public:
	MainGame();
	virtual ~MainGame() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnImGuiRender() override;
	void OnUpdate(Ember::DeltaTime DT) override;
	void OnEvent(Ember::Event& event) override;
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