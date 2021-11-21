#include "empch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Ember/Platform/OpenGL/OpenGLTexture.h"

namespace Ember
{
	Ref<Texture2D> Texture2D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EM_FATAL_ASSERT(false, "RendererAPI::None is not currently supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(filePath);
		}

		EM_FATAL_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}