#pragma once
#include "Ember/Renderer/RendererAPI.h"

namespace Ember
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height) override;

		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}