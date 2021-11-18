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
		case RendererAPI::API::None:
			EM_FATAL_ASSERT(false, "RendererAPI::None is not currently supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		EM_FATAL_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{

	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{

	}

	void VertexArray::Bind() const
	{

	}

	void VertexArray::UnBind() const
	{

	}
}