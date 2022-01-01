#include "empch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Ember
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // Need to Query the GPU to get this value in the future

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];
	};

	static Renderer2DData Data;

	void Renderer2D::Init()
	{
		EM_PROFILE_FUNCTION();

		Data.QuadVertexArray = VertexArray::Create();

		Data.QuadVertexBuffer = VertexBuffer::Create(Data.MaxVertices * sizeof(QuadVertex));
		Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3, "a_Position" },
			{ ShaderDataType::Vec4, "a_Colour" },
			{ ShaderDataType::Vec2, "a_TexCoord" },
			{ ShaderDataType::Vec, "a_TexIndex" },
			{ ShaderDataType::Vec, "a_TilingFactor" }
			});
		Data.QuadVertexArray->AddVertexBuffer(Data.QuadVertexBuffer);

		Data.QuadVertexBufferBase = new QuadVertex[Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, Data.MaxIndices);
		Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[Data.MaxTextureSlots];
		for (uint32_t i = 0; i < Data.MaxTextureSlots; i++)
			samplers[i] = i;

		Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		Data.TextureShader->Bind();
		Data.TextureShader->SetIntArray("u_Textures", samplers, Data.MaxTextureSlots);

		// Set all texture slots to 0
		Data.TextureSlots[0] = Data.WhiteTexture;

		Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Terminate()
	{
		EM_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		EM_PROFILE_FUNCTION();

		Data.TextureShader->Bind();
		Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		Data.QuadIndexCount = 0;
		Data.QuadVertexBufferPtr = Data.QuadVertexBufferBase;

		Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		EM_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)Data.QuadVertexBufferPtr - (uint8_t*)Data.QuadVertexBufferBase;
		Data.QuadVertexBuffer->SetData(Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < Data.TextureSlotIndex; i++)
			Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(Data.QuadVertexArray, Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, colour);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour)
	{
		EM_PROFILE_FUNCTION();

		const float texIndex = 0.0f; // White Texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[0];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = texIndex;
		Data.QuadVertexBufferPtr->TilingFactor = 1.0f;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[1];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = texIndex;
		Data.QuadVertexBufferPtr->TilingFactor = 1.0f;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[2];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = texIndex;
		Data.QuadVertexBufferPtr->TilingFactor = 1.0f;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[3];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = texIndex;
		Data.QuadVertexBufferPtr->TilingFactor = 1.0f;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		constexpr glm::vec4 colour = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < Data.TextureSlotIndex; i++)
		{
			if (*Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = texture;
			Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[0];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[1];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[2];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[3];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, colourTint, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < Data.TextureSlotIndex; i++)
		{
			if (*Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = texture;
			Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[0];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[1];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[2];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[3];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const glm::vec4& colour, float_t tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, colour, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const glm::vec4& colour, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		const float textureIndex = 0.0f; // White Texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[0];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[1];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[2];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[3];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		constexpr glm::vec4 colour = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < Data.TextureSlotIndex; i++)
		{
			if (*Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = texture;
			Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[0];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[1];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[2];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[3];
		Data.QuadVertexBufferPtr->Colour = colour;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, colourTint, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor)
	{
		EM_PROFILE_FUNCTION();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < Data.TextureSlotIndex; i++)
		{
			if (*Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = texture;
			Data.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[0];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[1];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[2];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = transform * Data.QuadVertexPositions[3];
		Data.QuadVertexBufferPtr->Colour = colourTint;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
	}
}