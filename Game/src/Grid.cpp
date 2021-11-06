#include "Grid.h"

void Grid::InitNewGrid(uint16_t x, uint16_t y)
{
	IntervalX = 2 / float(x);
	IntervalY = 2 / float(y);

	for (uint16_t j = 0; j < y; j++)
	{
		for (uint16_t i = 0; i < x; i++)
		{
			if (i == 0)
			{
				//Top-Left
				Vertices[j][i][0] = -1.0f;
				Vertices[j][i][1] = 1.0f - (IntervalY * j);
				Vertices[j][i][2] = 0.0f;

				//Top-Right
				Vertices[j][i][3] = -1.0f + IntervalX;
				Vertices[j][i][4] = 1.0f - (IntervalY * j);
				Vertices[j][i][5] = 0.0f;

				//Bottom-Left
				Vertices[j][i][6] = -1.0f;
				Vertices[j][i][7] = 1.0f - IntervalY - (IntervalY * j);
				Vertices[j][i][8] = 0.0f;

				//Bottom-Right
				Vertices[j][i][9] = -1.0f + IntervalX;
				Vertices[j][i][10] = 1.0f - IntervalY - (IntervalY * j);
				Vertices[j][i][11] = 0.0f;
			}
			if (i != 0)
			{
				//Top-Left
				Vertices[j][i][0] = -1.0f + (IntervalX * i);
				Vertices[j][i][1] = 1.0f - (IntervalY * j);
				Vertices[j][i][2] = 0.0f;

				//Top-Right
				Vertices[j][i][3] = -1.0f + (IntervalX * (i + 1));
				Vertices[j][i][4] = 1.0f - (IntervalY * j);
				Vertices[j][i][5] = 0.0f;

				//Bottom-Left
				Vertices[j][i][6] = -1.0f + (IntervalX * i);
				Vertices[j][i][7] = 1.0f - IntervalY - (IntervalY * j);
				Vertices[j][i][8] = 0.0f;

				//Bottom-Right
				Vertices[j][i][9] = -1.0f + (IntervalX * (i + 1));
				Vertices[j][i][10] = 1.0f - IntervalY - (IntervalY * j);
				Vertices[j][i][11] = 0.0f;
			}
		}
	}
}