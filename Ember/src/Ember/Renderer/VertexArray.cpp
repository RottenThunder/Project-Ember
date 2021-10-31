#include "empch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Ember/Platform/OpenGL/OpenGLVertexArray.h"

namespace Ember
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			EM_FATAL_ASSERT(false, "RendererAPI::None is not currently supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		EM_FATAL_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{

	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{

	}

	void VertexArray::Bind() const
	{

	}

	void VertexArray::UnBind() const
	{

	}
}