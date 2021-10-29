#pragma once
#include <string>
#include "Ember/Core/Core.h"

namespace Ember
{
	class EMBER_API Shader
	{
	private:
		uint32_t RendererID;
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;
	};
}