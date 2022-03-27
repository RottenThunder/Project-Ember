#pragma once
#include "Ember.h"

class Projectile
{
public:
	Projectile(glm::vec3 position, uint8_t travelDirection, float_t speed, float_t range);

	glm::vec3 Position;
	float_t Speed;
	float_t Rotation = 0.0f;
	uint8_t TravelDirection;
	float_t Range;
	bool CanDestroy = false;

	void Travel(Ember::DeltaTime deltaTime);
};