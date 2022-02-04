#pragma once
#include <Ember.h>
#include "Ember/Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>

class Entity
{
public:
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	Ember::Ref<Ember::Texture2D> Texture;
	bool IsCollidable = false;

	uint8_t CalculateAABBCollisions(const glm::vec3& pos, float Qx, float Qy);
};