#pragma once
#include <vector>
#include <fstream>
#include "Entity.h"

class LevelFileReader
{
private:
	std::fstream file;
	int8_t character1;
	int8_t character2;
	uint16_t lineCount = 0;
	uint16_t codeCount = 0;
	uint8_t codeCountTemp = 0;
	std::vector<Entity> RowOfEntities;
public:
	void Init(const std::string& levelFile);
	void Read(const std::string& levelFile);
	uint16_t GetLineCount();
	uint16_t GetCodeCount();
};