#include <Ember.h>

class NewLayer : public Ember::Layer
{
public:
	NewLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		EM_LOG_INFO("Example Layer is Updating!");
	}

	void OnEvent(Ember::Event& event) override
	{
		EM_LOG_TRACE("{0}", event);
	}
};

class GameApplication : public Ember::Application
{
public:
	GameApplication()
	{
		PushLayer(new NewLayer);
	}

	~GameApplication()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new GameApplication();
}