#include "Grid.h"

void Grid::InitNewGrid(uint16_t x, uint16_t y)
{
	IntervalX = 2 / float_t(x);
	IntervalY = 2 / float_t(y);

	//---Top Left Vertices---------------------------

	//Top-Left
	TopLeftVertices[0] = -1.0f;
	TopLeftVertices[1] = 1.0f;
	TopLeftVertices[2] = 0.0f;

	//Top-Right
	TopLeftVertices[3] = -1.0f + IntervalX;
	TopLeftVertices[4] = 1.0f;
	TopLeftVertices[5] = 0.0f;

	//Bottom-Left
	TopLeftVertices[6] = -1.0f;
	TopLeftVertices[7] = 1.0f - IntervalY;
	TopLeftVertices[8] = 0.0f;

	//Bottom-Right
	TopLeftVertices[9] = -1.0f + IntervalX;
	TopLeftVertices[10] = 1.0f - IntervalY;
	TopLeftVertices[11] = 0.0f;

	//-----------------------------------------------


	//---Bottom Right Vertices-----------------------

	//Top-Left
	BottomRightVertices[0] = 1.0f - IntervalX;
	BottomRightVertices[1] = -1.0f + IntervalY;
	BottomRightVertices[2] = 0.0f;

	//Top-Right
	BottomRightVertices[3] = 1.0f;
	BottomRightVertices[4] = -1.0f + IntervalY;
	BottomRightVertices[5] = 0.0f;

	//Bottom-Left
	BottomRightVertices[6] = 1.0f - IntervalX;
	BottomRightVertices[7] = -1.0f;
	BottomRightVertices[8] = 0.0f;

	//Bottom-Right
	BottomRightVertices[9] = 1.0f;
	BottomRightVertices[10] = -1.0f;
	BottomRightVertices[11] = 0.0f;

	//-----------------------------------------------
}