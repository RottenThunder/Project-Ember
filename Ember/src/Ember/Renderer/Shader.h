#pragma once
#include <string>
#include "Ember/Core/Core.h"
#include "glm/glm.hpp"

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

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}