#include "LevelFileReader.h"

std::unordered_map<uint32_t, std::string> LevelFileReader::Init(const std::string& levelFile)
{
	std::unordered_map<uint32_t, std::string> mapData;
	file.open(levelFile, std::ios::in);
	if (file.is_open())
	{
		std::string currentLine;
		std::string strWidth;
		std::string strHeight;
		std::getline(file, currentLine);
		size_t diff1 = currentLine.find("x");
		size_t diff2 = currentLine.find("/");
		for (size_t i = 0; i < diff1; i++)
		{
			strWidth.append(1, currentLine.at(i));
		}
		for (size_t i = diff1 + 1; i < diff2; i++)
		{
			strHeight.append(1, currentLine.at(i));
		}
		width = std::stoi(strWidth);
		height = std::stoi(strHeight);

		uint32_t k = 0;

		for (uint16_t i = 0; i < height; i++)
		{
			std::getline(file, currentLine);

			for (uint32_t j = 0; j < currentLine.size(); j = j + 3)
			{
				k++;
				std::string hexCode;
				hexCode.append(1, currentLine.at(j));
				hexCode.append(1, currentLine.at(j + 1));
				std::unordered_map<std::string, std::string>::const_iterator temp = TileDataBase.find(hexCode);
				mapData.insert(std::pair(k, temp->second));
			}
		}
	}
	file.close();
	return mapData;
}

uint16_t LevelFileReader::GetCurrentWidth()
{
	return width;
}

uint16_t LevelFileReader::GetCurrentHeight()
{
	return height;
}