#pragma once
#include <iostream>

class Grid
{
public:
	void InitNewGrid(uint16_t x, uint16_t y);
	float_t ObjectOriginWithoutTexCoords[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	float_t ObjectOriginWithTexCoords[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f
	};

	float_t CharacterOriginWithoutTexCoords[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 1.5f, 0.0f,
		0.5f, 1.5f, 0.0f,
	};

	float_t CharacterOriginWithTexCoords[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 1.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 1.5f, 0.0f, 1.0f, 1.0f
	};

	float_t TopLeftVertices[12];
	float_t BottomRightVertices[12];
	float_t IntervalX;
	float_t IntervalY;
};