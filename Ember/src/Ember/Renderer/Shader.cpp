#include "empch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Ember/Platform/OpenGL/OpenGLShader.h"

namespace Ember
{
	Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EM_FATAL_ASSERT(false, "RendererAPI::None is not currently supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filePath);
		}

		EM_FATAL_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EM_FATAL_ASSERT(false, "RendererAPI::None is not currently supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		EM_FATAL_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}