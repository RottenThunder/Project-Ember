#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Ember/Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), OrthoCameraController(16.0f / 9.0f)
{

}

void Sandbox2D::OnAttach()
{
	squareVertexArray = Ember::VertexArray::Create();

	float_t SquareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	Ember::Ref<Ember::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer.reset(Ember::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

	squareVertexBuffer->SetLayout({
		{ Ember::ShaderDataType::Vec3, "a_Position", false }
		});

	squareVertexArray->AddVertexBuffer(squareVertexBuffer);

	Ember::Ref<Ember::IndexBuffer> squareIndexBuffer;
	uint32_t squareIndices[6] = { 3, 2, 0, 0, 1, 3 };
	squareIndexBuffer.reset(Ember::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

	squareVertexArray->SetIndexBuffer(squareIndexBuffer);

	squareShader = Ember::Shader::Create("assets/shaders/FlatColour.glsl");
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

	std::dynamic_pointer_cast<Ember::OpenGLShader>(squareShader)->Bind();
	std::dynamic_pointer_cast<Ember::OpenGLShader>(squareShader)->UploadUniformFloat4("u_Colour", squareColour);

	Ember::Renderer::BeginScene(OrthoCameraController.GetCamera());

	Ember::Renderer::Submit(squareShader, squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Ember::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Ember::Event& event)
{
	OrthoCameraController.OnEvent(event);
}