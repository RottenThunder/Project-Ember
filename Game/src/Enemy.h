#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	float MaxHealth;
	float Health;
	Ember::Ref<Ember::Texture2D> EmptyHealthBar;
};