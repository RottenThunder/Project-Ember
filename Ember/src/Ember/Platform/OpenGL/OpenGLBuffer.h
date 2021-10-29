#pragma once
#include "Ember/Core/Core.h"
#include "Ember/Renderer/Buffer.h"

namespace Ember
{
	class EMBER_API OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t RendererID;
	public:
		OpenGLVertexBuffer(float_t* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;
	};

	class EMBER_API OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t RendererID;
		uint32_t Count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

		virtual uint32_t GetCount() const { return Count; }
	};
}