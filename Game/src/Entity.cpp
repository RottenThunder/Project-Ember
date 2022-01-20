#include "Entity.h"

uint8_t Entity::CalculateAABBCollisions(const glm::vec3& pos, float Qx, float Qy)
{
	//P = This Entity
	//Q = Other Entity

	float Px = pos.x - 0.5f;
	float Py = pos.y - 1.0f;

	if (Px < (Qx + 1.0f) && (Px + 1.0f) > Qx && Py < (Qy + 1.0f) && (Py + 1.0f) > Qy)
	{
		return 1;
	}

	return 0;
}