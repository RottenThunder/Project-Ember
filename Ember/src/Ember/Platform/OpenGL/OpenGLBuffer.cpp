#include "empch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Ember
{
	// OpenGL Vertex Buffers

	OpenGLVertexBuffer::OpenGLVertexBuffer(float_t* vertices, uint32_t size)
	{
		EM_PROFILE_FUNCTION();

		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		EM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	// OpenGL Index Buffers


	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: Count(count)
	{
		EM_PROFILE_FUNCTION();

		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		EM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		EM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}