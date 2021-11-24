#pragma once
#include "Player.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class CollisionHandler
{
public:
	bool CanMovePositiveX = true;
	bool CanMoveNegativeX = true;
	bool CanMovePositiveY = true;
	bool CanMoveNegativeY = true;

	void HandleCollisionsForPlayer(Player& player, const glm::vec2& minColliderValues, const glm::vec2& maxColliderValues);
	void BlockMovementForPlayer(const Player& player, const glm::vec2& minColliderValues, const glm::vec2& maxColliderValues);
};