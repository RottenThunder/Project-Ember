#pragma once
#include <iostream>

class Grid
{
public:
	void InitNewGrid(uint16_t x, uint16_t y);
	float_t TopLeftVertices[12];
	float_t BottomRightVertices[12];
	float_t IntervalX;
	float_t IntervalY;
};