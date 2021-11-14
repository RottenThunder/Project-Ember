#pragma once
#include "Ember/Renderer/Shader.h"
#include "Ember/Core/Core.h"
#include <glm/glm.hpp>

namespace Ember
{
	class EMBER_API OpenGLShader : public Shader
	{
	private:
		uint32_t RendererID;
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformInt(const std::string& name, int32_t value);

		void UploadUniformFloat(const std::string& name, float_t value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}