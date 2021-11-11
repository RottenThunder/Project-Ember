#pragma once
#include <stdint.h>

class PlayerPos
{
public:
	uint8_t CurrentPosX = 0;
	uint8_t CurrentPosY = 0;
	uint8_t MaxPosX;
	uint8_t MaxPosY;
};

class MonsterPos
{
public:
	uint8_t CurrentPosX;
	uint8_t CurrentPosY;
	uint8_t MaxPosX;
	uint8_t MaxPosY;
};