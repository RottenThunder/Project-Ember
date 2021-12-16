#include "empch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Ember
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Vec:
			return GL_FLOAT;
		case ShaderDataType::Vec2:
			return GL_FLOAT;
		case ShaderDataType::Vec3:
			return GL_FLOAT;
		case ShaderDataType::Vec4:
			return GL_FLOAT;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::Int2:
			return GL_INT;
		case ShaderDataType::Int3:
			return GL_INT;
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}

		EM_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		EM_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		EM_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		EM_PROFILE_FUNCTION();

		glBindVertexArray(RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		EM_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		EM_PROFILE_FUNCTION();

		EM_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}
		VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		EM_PROFILE_FUNCTION();

		glBindVertexArray(RendererID);
		indexBuffer->Bind();
		Index_Buffer = indexBuffer;
	}
}