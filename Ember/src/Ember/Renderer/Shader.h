#pragma once
#include <string>
#include "Ember/Core/Core.h"

namespace Ember
{
	class EMBER_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& filePath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}