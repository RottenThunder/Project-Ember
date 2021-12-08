#include "empch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Ember
{
	OrthographicCamera::OrthographicCamera(float_t left, float_t right, float_t bottom, float_t top)
		: ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), ViewMatrix(1.0f)
	{
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float_t left, float_t right, float_t bottom, float_t top)
	{
		ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0, 0, 1));

		ViewMatrix = glm::inverse(transform);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}
}