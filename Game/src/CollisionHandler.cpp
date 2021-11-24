#include "CollisionHandler.h"

void CollisionHandler::HandleCollisionsForPlayer(Player& player, const glm::vec2& minColliderValues, const glm::vec2& maxColliderValues)
{
	if ((player.ColliderBottomRight.x >= minColliderValues.x && player.ColliderBottomRight.y >= minColliderValues.y) &&
		(player.ColliderBottomRight.x <= maxColliderValues.x && player.ColliderBottomRight.y <= maxColliderValues.y))
	{
		player.BottomRightColliding = true;
	}
	if (!((player.ColliderBottomRight.x >= minColliderValues.x && player.ColliderBottomRight.y >= minColliderValues.y) &&
		(player.ColliderBottomRight.x <= maxColliderValues.x && player.ColliderBottomRight.y <= maxColliderValues.y)))
	{
		player.BottomRightColliding = false;
	}

	if ((player.ColliderTopRight.x >= minColliderValues.x && player.ColliderTopRight.y >= minColliderValues.y) &&
		(player.ColliderTopRight.x <= maxColliderValues.x && player.ColliderTopRight.y <= maxColliderValues.y))
	{
		player.TopRightColliding = true;
	}
	if (!((player.ColliderTopRight.x >= minColliderValues.x && player.ColliderTopRight.y >= minColliderValues.y) &&
		(player.ColliderTopRight.x <= maxColliderValues.x && player.ColliderTopRight.y <= maxColliderValues.y)))
	{
		player.TopRightColliding = false;
	}

	if ((player.ColliderBottomLeft.x >= minColliderValues.x && player.ColliderBottomLeft.y >= minColliderValues.y) &&
		(player.ColliderBottomLeft.x <= maxColliderValues.x && player.ColliderBottomLeft.y <= maxColliderValues.y))
	{
		player.BottomLeftColliding = true;
	}
	if (!((player.ColliderBottomLeft.x >= minColliderValues.x && player.ColliderBottomLeft.y >= minColliderValues.y) &&
		(player.ColliderBottomLeft.x <= maxColliderValues.x && player.ColliderBottomLeft.y <= maxColliderValues.y)))
	{
		player.BottomLeftColliding = false;
	}

	if ((player.ColliderTopLeft.x >= minColliderValues.x && player.ColliderTopLeft.y >= minColliderValues.y) &&
		(player.ColliderTopLeft.x <= maxColliderValues.x && player.ColliderTopLeft.y <= maxColliderValues.y))
	{
		player.TopLeftColliding = true;
	}
	if (!((player.ColliderTopLeft.x >= minColliderValues.x && player.ColliderTopLeft.y >= minColliderValues.y) &&
		(player.ColliderTopLeft.x <= maxColliderValues.x && player.ColliderTopLeft.y <= maxColliderValues.y)))
	{
		player.TopLeftColliding = false;
	}
}

void CollisionHandler::BlockMovementForPlayer(const Player& player, const glm::vec2& minColliderValues, const glm::vec2& maxColliderValues)
{
	if (player.BottomRightColliding || player.TopRightColliding)
	{
		CanMovePositiveX = false;
	}
	else
	{
		CanMovePositiveX = true;
	}

	if (player.TopRightColliding || player.TopLeftColliding)
	{
		CanMovePositiveY = false;
	}
	else
	{
		CanMovePositiveY = true;
	}

	if (player.TopLeftColliding || player.BottomLeftColliding)
	{
		CanMoveNegativeX = false;
	}
	else
	{
		CanMoveNegativeX = true;
	}

	if (player.BottomLeftColliding || player.BottomRightColliding)
	{
		CanMoveNegativeY = false;
	}
	else
	{
		CanMoveNegativeY = true;
	}

	/*
	if (player.TopRightColliding)
	{
		if (player.BottomRightColliding)
		{
			CanMovePositiveX = false;
		}
		if (player.TopLeftColliding)
		{
			CanMovePositiveY = false;
		}
		if (!(player.BottomRightColliding) && !(player.TopLeftColliding) && !(player.BottomLeftColliding))
		{
			if (((player.ColliderTopRight.x - 0.1f) < minColliderValues.x) && (minColliderValues.y < player.ColliderTopRight.y) && (minColliderValues.y > player.ColliderBottomRight.y))
			{
				CanMovePositiveX = false;
			}
			if (((player.ColliderTopRight.y - 0.1f) < minColliderValues.y) && (minColliderValues.x < player.ColliderTopRight.x) && (minColliderValues.x > player.ColliderTopLeft.x))
			{
				CanMovePositiveY = false;
			}
			if (!(CanMovePositiveX) && !(CanMovePositiveY))
			{
				CanMovePositiveX = true;
				CanMovePositiveY = true;
			}
		}
	}
	else
	{
		CanMovePositiveX = true;
		CanMovePositiveY = true;
	}

	if (player.TopLeftColliding)
	{
		if (player.BottomLeftColliding)
		{
			CanMoveNegativeX = false;
		}
		if (player.TopRightColliding)
		{
			CanMovePositiveY = false;
		}
		if (!(player.BottomRightColliding) && !(player.TopRightColliding) && !(player.BottomLeftColliding))
		{
			if (((player.ColliderTopLeft.x + 0.1f) > minColliderValues.x) && (minColliderValues.y < player.ColliderTopLeft.y) && (minColliderValues.y > player.ColliderBottomLeft.y))
			{
				CanMoveNegativeX = false;
			}
			if (((player.ColliderTopLeft.y - 0.1f) < minColliderValues.y) && (maxColliderValues.x < player.ColliderTopRight.x) && (maxColliderValues.x > player.ColliderTopLeft.x))
			{
				CanMovePositiveY = false;
			}
			if (!(CanMoveNegativeX) && !(CanMovePositiveY))
			{
				CanMoveNegativeX = true;
				CanMovePositiveY = true;
			}
		}
	}
	else
	{
		CanMoveNegativeX = true;
		CanMovePositiveY = true;
	}
	*/



	/*
	if (player.BottomRightColliding || player.TopRightColliding)
	{
		CanMovePositiveX = false;
	}
	else
	{
		CanMovePositiveX = true;
	}

	if (player.TopRightColliding || player.TopLeftColliding)
	{
		CanMovePositiveY = false;
	}
	else
	{
		CanMovePositiveY = true;
	}

	if (player.TopLeftColliding || player.BottomLeftColliding)
	{
		CanMoveNegativeX = false;
	}
	else
	{
		CanMoveNegativeX = true;
	}

	if (player.BottomLeftColliding || player.BottomRightColliding)
	{
		CanMoveNegativeY = false;
	}
	else
	{
		CanMoveNegativeY = true;
	}
	*/
}