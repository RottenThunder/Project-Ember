#pragma once
#include "Ember/Core/Core.h"
#include "glm/glm.hpp"

namespace Ember
{
	class EMBER_API OrthographicCamera
	{
	private:
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ViewProjectionMatrix;
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;

		void RecalculateViewMatrix();
	public:
		OrthographicCamera(float_t left, float_t right, float_t bottom, float_t top);

		void SetProjection(float_t left, float_t right, float_t bottom, float_t top);
		void SetPosition(const glm::vec3& position) { Position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { Rotation = rotation; RecalculateViewMatrix(); }

		const glm::vec3& GetPosition() const { return Position; }
		float GetRotation() const { return Rotation; }

		const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMatrix; }
	};
}