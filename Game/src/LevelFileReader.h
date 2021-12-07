#pragma once
#include <fstream>
#include "Entity.h"

class LevelFileReader
{
private:
	std::ifstream file;
	uint16_t width;
	uint16_t height;

	std::unordered_map<std::string, std::string> TileDataBase =
	{
		{"00", "assets/textures/Checkerboard_RGB.png"}
	};

public:
	std::unordered_map<uint32_t, std::string> Init(const std::string& levelFile);

	uint16_t GetCurrentWidth();
	uint16_t GetCurrentHeight();
};