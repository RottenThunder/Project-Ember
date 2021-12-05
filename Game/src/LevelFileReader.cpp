#include "LevelFileReader.h"

void LevelFileReader::Init(const std::string& levelFile)
{
	lineCount = 0;
	codeCount = 0;
	codeCountTemp = 0;
	file.open(levelFile, std::ios::in);
	while (!(file.eof()))
	{
		file >> character1;
		if (character1 == 47)
		{
			lineCount++;
		}
		if (lineCount == 0)
		{
			if ((character1 >= 48 && character1 <= 57) || (character1 >= 65 && character1 <= 70))
			{
				codeCountTemp++;
			}
			if (codeCountTemp == 2)
			{
				codeCountTemp = 0;
				codeCount++;
			}
		}
	}
	lineCount--;
	file.close();
}

void LevelFileReader::Read(const std::string& levelFile)
{
	file.open(levelFile, std::ios::in);

	for (uint16_t i = 0; i < codeCount; i++)
	{
		file >> character1;
		file >> character2;
		//Function to check Both characters
		if (character1 == 48 && character2 == 48)
		{
			Entity entity;
			RowOfEntities.push_back(entity);
			RowOfEntities.at(i).Init(false, "assets/textures/Checkerboard_RGB.png");
		}
		file >> character1;
	}

	file.close();
}

uint16_t LevelFileReader::GetLineCount()
{
	return lineCount;
}

uint16_t LevelFileReader::GetCodeCount()
{
	return codeCount;
}