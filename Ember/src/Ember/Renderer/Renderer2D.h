#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"

namespace Ember
{
	class EMBER_API Renderer2D
	{
	public:
		static void Init();
		static void Terminate();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		//Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float_t tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float_t tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const glm::vec4& colour, float_t tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const glm::vec4& colour, float_t tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, float_t tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, float_t tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float_t rotation, const Ref<Texture2D>& texture, const glm::vec4& colourTint, float_t tilingFactor = 1.0f);
	};
}