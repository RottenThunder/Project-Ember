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
		{"00", "assets/textures/Black_Tile.png"},
		{"01", "assets/textures/Checkerboard_Tile.png"},
		{"0A", "assets/textures/Dungeon_Wall_TL_Corner.png"},
		{"0B", "assets/textures/Dungeon_Wall_TR_Corner.png"},
		{"0C", "assets/textures/Dungeon_Wall_BL_Corner.png"},
		{"0D", "assets/textures/Dungeon_Wall_BR_Corner.png"}
	};

public:
	std::unordered_map<uint32_t, std::string> Init(const std::string& levelFile);

	uint16_t GetCurrentWidth();
	uint16_t GetCurrentHeight();
};