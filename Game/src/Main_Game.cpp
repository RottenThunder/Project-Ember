#include <Ember.h>

class NewLayer : public Ember::Layer
{
public:
	NewLayer()
		: Layer("Example") {}
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