#pragma once
#include "RendererAPI.h"

namespace Ember
{
	class EMBER_API RenderCommand
	{
	private:
		static RendererAPI* rendererAPI;
	public:
		inline static void SetClearColour(const glm::vec4& colour)
		{
			rendererAPI->SetClearColour(colour);
		}

		inline static void Clear()
		{
			rendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			rendererAPI->DrawIndexed(vertexArray);
		}
	};
}