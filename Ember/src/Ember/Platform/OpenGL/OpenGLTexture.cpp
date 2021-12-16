#include "empch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"

namespace Ember
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)
		: FilePath(filePath)
	{
		EM_PROFILE_FUNCTION();

		int32_t width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			EM_PROFILE_SCOPE("stbi_load() - OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)");
			data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		}
		EM_FATAL_ASSERT(data, "Failed to load Image!");
		Width = width;
		Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		InternalFormat = internalFormat;
		DataFormat = dataFormat;

		EM_FATAL_ASSERT(internalFormat & dataFormat, "Format Not Supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
		glTextureStorage2D(RendererID, 1, internalFormat, Width, Height);

		glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(RendererID, 0, 0, 0, Width, Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: Width(width), Height(height)
	{
		EM_PROFILE_FUNCTION();

		InternalFormat = GL_RGBA8;
		DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
		glTextureStorage2D(RendererID, 1, InternalFormat, Width, Height);

		glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		EM_PROFILE_FUNCTION();

		glDeleteTextures(1, &RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		EM_PROFILE_FUNCTION();

		uint32_t bytesPerPixel = DataFormat == GL_RGBA ? 4 : 3;
		EM_FATAL_ASSERT(size == Width * Height * bytesPerPixel, "Data must cover the entire Texture!!!");
		glTextureSubImage2D(RendererID, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		EM_PROFILE_FUNCTION();

		glBindTextureUnit(slot, RendererID);
	}
}