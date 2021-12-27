#pragma once
#include "RendererAPI.h"

namespace Ember
{
	class EMBER_API RenderCommand
	{
	private:
		static RendererAPI* rendererAPI;
	public:
		inline static void Init()
		{
			rendererAPI->Init();
		}

		inline static void SetViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
		{
			rendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColour(const glm::vec4& colour)
		{
			rendererAPI->SetClearColour(colour);
		}

		inline static void Clear()
		{
			rendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			rendererAPI->DrawIndexed(vertexArray, count);
		}
	};
}