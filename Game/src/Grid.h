#pragma once
#include <iostream>

class Grid
{
private:
	float IntervalX;
	float IntervalY;
public:
	void InitNewGrid(uint16_t x, uint16_t y);
	float_t Vertices[100][100][12];
};