#pragma once
#include "Ember/Core/Core.h"

namespace Ember
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class EMBER_API Renderer
	{
	private:
		static RendererAPI rendererAPI;
	public:
		inline static RendererAPI GetAPI() { return rendererAPI; }
	};
}