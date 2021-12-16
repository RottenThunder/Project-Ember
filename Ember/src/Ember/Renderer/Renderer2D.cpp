#include "empch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Ember
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* Data;

	void Renderer2D::Init()
	{
		EM_PROFILE_FUNCTION();

		Data = new Renderer2DStorage;

		Data->QuadVertexArray = VertexArray::Create();

		float_t SquareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f
		};

		Ref<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

		squareVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3, "a_Position", false },
			{ ShaderDataType::Vec2, "a_TexCoord", false }
			});

		Data->QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

		Ref<IndexBuffer> squareIndexBuffer;
		uint32_t squareIndices[6] = { 3, 2, 0, 0, 1, 3 };
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

		Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		Data->TextureShader->Bind();
		Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Terminate()
	{
		EM_PROFILE_FUNCTION();

		delete Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->Bind();
		Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		EM_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour, float_t tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, colour, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("u_Colour", colour);
		Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", transform);

		Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("u_Colour", glm::vec4(1.0f));
		Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", transform);

		Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, colourTint, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("u_Colour", colourTint);
		Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", transform);

		Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const glm::vec4& colour, float_t tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, colour, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const glm::vec4& colour, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("u_Colour", colour);
		Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", transform);

		Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("u_Colour", glm::vec4(1.0f));
		Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", transform);

		Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, colourTint, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("u_Colour", colourTint);
		Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("u_Transform", transform);

		Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(Data->QuadVertexArray);
	}
}