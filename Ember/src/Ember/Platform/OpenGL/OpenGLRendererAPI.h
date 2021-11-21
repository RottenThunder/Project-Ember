#pragma once
#include "Ember/Renderer/RendererAPI.h"

namespace Ember
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}