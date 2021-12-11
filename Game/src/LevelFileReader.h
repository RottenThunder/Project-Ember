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
		{"11", "assets/textures/Dungeon_Floor_TL_Corner.png"},
		{"12", "assets/textures/Dungeon_Floor_TR_Corner.png"},
		{"13", "assets/textures/Dungeon_Floor_BL_Corner.png"},
		{"14", "assets/textures/Dungeon_Floor_BR_Corner.png"},
		{"15", "assets/textures/Dungeon_Floor_North.png"},
		{"16", "assets/textures/Dungeon_Floor_East.png"},
		{"17", "assets/textures/Dungeon_Floor_South.png"},
		{"18", "assets/textures/Dungeon_Floor_West.png"},
		{"19", "assets/textures/Dungeon_Floor_Main.png"},
		{"1A", "assets/textures/Dungeon_Wall_TL_Corner.png"},
		{"1B", "assets/textures/Dungeon_Wall_TR_Corner.png"},
		{"1C", "assets/textures/Dungeon_Wall_BL_Corner.png"},
		{"1D", "assets/textures/Dungeon_Wall_BR_Corner.png"},
		{"1E", "assets/textures/Dungeon_Wall_North.png"},
		{"1F", "assets/textures/Dungeon_Wall_East.png"},
		{"1G", "assets/textures/Dungeon_Wall_South.png"},
		{"1H", "assets/textures/Dungeon_Wall_West.png"}
	};

public:
	std::unordered_map<uint32_t, std::string> Init(const std::string& levelFile);

	uint16_t GetCurrentWidth();
	uint16_t GetCurrentHeight();
};