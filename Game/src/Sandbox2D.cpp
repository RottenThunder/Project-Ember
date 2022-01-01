#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), OrthoCameraController(16.0f / 9.0f)
{

}

void Sandbox2D::OnAttach()
{
	EM_PROFILE_FUNCTION();

	CheckerboardTexture = Ember::Texture2D::Create("assets/textures/Checkerboard_Tile.png");
}

void Sandbox2D::OnDetach()
{
	EM_PROFILE_FUNCTION();
}

void Sandbox2D::OnImGuiRender()
{
	EM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Colour", glm::value_ptr(squareColour));
	ImGui::End();
}

void Sandbox2D::OnUpdate(Ember::DeltaTime DT)
{
	EM_PROFILE_FUNCTION();

	OrthoCameraController.OnUpdate(DT);

	{
		EM_PROFILE_SCOPE("Render Prep");
		Ember::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ember::RenderCommand::Clear();
	}

	{
		EM_PROFILE_SCOPE("Render Draw");

		static float rotation = 0.0f;
		rotation += DT * 50.0f;

		Ember::Renderer2D::BeginScene(OrthoCameraController.GetCamera());

		Ember::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Ember::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 0.35f, 1.73f }, { 0.1f, 0.2f, 0.9f, 1.0f });
		Ember::Renderer2D::DrawQuad({ -2.0f, -1.0f }, { 0.85f, 1.0f }, { 0.3f, 0.5f, 0.3f, 1.0f });
		Ember::Renderer2D::DrawQuad({ 0.0f, 3.0f }, { 1.85f, 1.0f }, { 0.9f, 0.4f, 0.1f, 1.0f });

		Ember::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, CheckerboardTexture, 10.0f);
		Ember::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, CheckerboardTexture, 20.0f);

		Ember::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, rotation, CheckerboardTexture, { 0.8f, 0.2f, 0.3f, 1.0f });

		Ember::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnEvent(Ember::Event& event)
{
	OrthoCameraController.OnEvent(event);
}