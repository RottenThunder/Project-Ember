#pragma once
#include "Ember/Renderer/Texture.h"

namespace Ember
{
	class EMBER_API OpenGLTexture2D : public Texture2D
	{
	private:
		std::string FilePath;
		uint32_t Width, Height;
		uint32_t RendererID;
	public:
		OpenGLTexture2D(const std::string& filePath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return Width; }
		virtual uint32_t GetHeight() const override { return Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	};
}