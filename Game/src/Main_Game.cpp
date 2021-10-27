#include <Ember.h>

class NewLayer : public Ember::Layer
{
public:
	NewLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Ember::Input::IsKeyPressed(EM_KEY_W))
		{
			EM_LOG_TRACE("W Key was Pressed!");
		}
	}

	void OnEvent(Ember::Event& event) override
	{
		if (event.GetEventType() == Ember::EventType::KeyPressed)
		{
			Ember::KeyPressedEvent& e = (Ember::KeyPressedEvent&)event;
			EM_LOG_INFO("{0}", char(e.GetKeyCode()));
		}
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