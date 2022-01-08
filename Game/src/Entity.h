#pragma once
#include <Ember.h>
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "Grid.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>

class Entity
{
private:
	Grid grid;
public:
	glm::u8vec4 NumberOfCollisions = { 0, 0, 0, 0 }; //X is +x, Y is +y, Z is -x, W is -y
	glm::u8vec4 CollidersActive = { 0, 0, 0, 0 }; //X is Top-Left, Y is Top-Right, Z is Bottom-Left, W is Bottom-Right
	bool IsCollidable = false;
	Ember::Ref<Ember::Texture2D> Texture;
	glm::mat4 Transform;
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };

	void CalculateCollisions(const glm::vec3& ColliderCentre);
	void HandleCollisions(bool& CanMovePositiveX, bool& CanMoveNegativeX, bool& CanMovePositiveY, bool& CanMoveNegativeY);
};