#include <Ember.h>

class GameApplication : public Ember::Application
{
public:
	GameApplication()
	{

	}

	~GameApplication()
	{

	}
};

Ember::Application* Ember::CreateApplication()
{
	return new GameApplication();
}