#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), OrthoCameraController(16.0f / 9.0f)
{

}

void Sandbox2D::OnAttach()
{
	CheckerboardTexture = Ember::Texture2D::Create("assets/textures/Checkerboard_Tile.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Colour", glm::value_ptr(squareColour));
	ImGui::End();
}

void Sandbox2D::OnUpdate(Ember::DeltaTime DT)
{
	OrthoCameraController.OnUpdate(DT);

	Ember::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
	Ember::RenderCommand::Clear();

	Ember::Renderer2D::BeginScene(OrthoCameraController.GetCamera());

	Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Ember::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 0.35f, 1.73f }, { 0.1f, 0.2f, 0.9f, 1.0f });
	Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, CheckerboardTexture);

	Ember::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Ember::Event& event)
{
	OrthoCameraController.OnEvent(event);
}