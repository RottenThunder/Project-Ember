#include "Projectile.h"

Projectile::Projectile(glm::vec3 position, uint8_t travelDirection, float_t speed, float_t range)
	: Position(position), TravelDirection(travelDirection), Speed(speed), Range(range)
{

}

void Projectile::Travel(Ember::DeltaTime deltaTime)
{
	switch (TravelDirection)
	{
	case 0: //PlayerFace::Down
		Position.y -= Speed * deltaTime;
		break;
	case 1: //PlayerFace::Left
		Position.x -= Speed * deltaTime;
		break;
	case 2: //PlayerFace::Up
		Position.y += Speed * deltaTime;
		break;
	case 3: //PlayerFace::Right
		Position.x += Speed * deltaTime;
		break;
	}

	Range -= Speed * deltaTime;
	if (Range <= 0.0f)
	{
		CanDestroy = true;
	}

	Rotation += 10.0f;
}