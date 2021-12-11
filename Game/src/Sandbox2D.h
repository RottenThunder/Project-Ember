#pragma once
#include <Ember.h>

class Sandbox2D : public Ember::Layer
{
private:
	Ember::OrthographicCameraController OrthoCameraController;
	Ember::Ref<Ember::VertexArray> squareVertexArray;
	Ember::Ref<Ember::Shader> squareShader;
	glm::vec4 squareColour = { 0.9f, 0.1f, 0.4f, 1.0f };
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnImGuiRender() override;
	void OnUpdate(Ember::DeltaTime DT) override;
	void OnEvent(Ember::Event& event) override;
};