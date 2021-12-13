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
	Ember::Ref<Ember::VertexArray> EntityVertexArray;
	Ember::Ref<Ember::VertexBuffer> EntityVertexBuffer;
	Ember::Ref<Ember::IndexBuffer> EntityIndexBuffer;
	Ember::Ref<Ember::Shader> EntityTextureShader;
	Ember::Ref<Ember::Texture2D> EntityTexture;
	glm::mat4 EntityTransform;
	glm::vec3 EntityPosition = { 0.0f, 0.0f, 0.0f };

	void CalculateCollisions(const glm::vec3& ColliderCentre);
	void HandleCollisions(bool& CanMovePositiveX, bool& CanMoveNegativeX, bool& CanMovePositiveY, bool& CanMoveNegativeY);
};